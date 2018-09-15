#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct List {
	int number;
	char ** line;
};

struct List * strings_division(struct List * output, char * array_intput, char * special_symbols);

int main() {
	struct List * line = NULL;
	char input_string[100] = {0};
	char symbols[20] = {0};
	int counter = -1;
	do {
		counter++;
		assert(counter < 100);
		input_string[counter] = getchar();
	} while( input_string[counter] != '\n');
	input_string[counter] = '\0';
	counter = -1;
	do {
		counter++;
		assert(counter < 20);
		symbols[counter] = getchar();
	} while(symbols[counter] != '\n');
	symbols[counter] = '\0';
	line = strings_division(line, input_string, symbols);
	assert(line->number);
	printf("\nYour strings: \n");
	for(counter = 0; counter < line->number; counter++) {
		assert(line->line[counter]);
		printf("%s\n", line->line[counter]);
	}
	printf("The number of strings: %d\n", line->number);
	free(line->line);
	free(line);
	return 0;
}

struct List * strings_division(struct List * output, char * array, char * array_sign) {
	assert(!output);
	int array_lenght = 0;
	int counter_1 = 0;
	int counter_2 = 0;
	output = (struct List *)calloc(1, sizeof(struct List));
	output->line = (char**)calloc(100, sizeof(char*));
	output->line[output->number] = array;
	output->number++;
	for(; array[counter_1] != '\0'; counter_1++) {
		for(counter_2 = 0; array_sign[counter_2] != '\0'; counter_2++) {
			if(array[counter_1] == array_sign[counter_2]) array[counter_1] = '\0';
		}
	}
	array_lenght = counter_1;
	for(counter_1 = 0; counter_1 < array_lenght; counter_1++) {
		if(array[counter_1] == '\0' && array[counter_1 + 1] != '\0') {
		output->line[output->number] = array + counter_1 + 1;
		output->number++;
		}
	}
	return output;
}
