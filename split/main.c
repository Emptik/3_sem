#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_SIZE 1000
#define MAX_DELIMITER_NUMBER 20
#define MAX_LINES_NUMBER 100

struct words {
	size_t number_of_lines;
	char **lines;
};

struct words *divide(char *your_string, char *special_symbols);
void destroy(struct words *line);
struct words *create();
void fill(char *input_string, char *symbols);

int main() {
	int i = 0;
	struct words *date = NULL;
	char input_string[MAX_STRING_SIZE] = {0};
	char delimitors[MAX_DELIMITER_NUMBER] = {0};
	fill(input_string, delimitors);
	date = divide(input_string, delimitors);
	printf("\nYour strings: \n");
	for (i = 0; i < date->number_of_lines; i++) {
		assert(date->lines[i]);
		printf("%s\n", date->lines[i]);
	}
	printf("The number of strings: %lu\n", date->number_of_lines);
	destroy(date);
	return 0;
}

void fill(char *input_string, char *symbols) {
	printf("Enter your string, use \\n to complete the line input:\n");
	fgets(input_string, MAX_STRING_SIZE, stdin);
	printf("Enter your delimitors, use \\n to complete the line input:\n");
	fgets(symbols, MAX_DELIMITER_NUMBER, stdin);
}

struct words *divide(char *your_string, char *special_symbols) {
	struct words * output = NULL;
	output = create();
	output->lines[output->number_of_lines] = strtok(your_string, special_symbols);
	while (output->lines[output->number_of_lines] != NULL) {
		output->number_of_lines++;
		output->lines[output->number_of_lines] = strtok(NULL, special_symbols);
	}
	return output;
}

void destroy(struct words *line) {
	free(line->lines);
	free(line);
}

struct words *create() {
	struct words *output = NULL;
	output = (struct words *)calloc(1, sizeof(struct words));
	output->lines = (char**)calloc(MAX_LINES_NUMBER, sizeof(char*));
	return output;
}
