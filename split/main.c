#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STRING_SIZE	1000
#define MAX_DELIMITER_NUMBER	20
#define MAX_LINES_NUMBER	100

// почему вы решили назвать эти структуру "хранилище строк"?
// почему не "words" или "tokens"?
struct lines_storage {
	size_t number_of_lines;
	char ** lines;
};

// что-то странное у вас с отступами в следующих 4х строках
// как-то не можете вы определиться, ставите ли вы пробелы вокруг * и где именно ... сейчас у вас 2 варианта присутствуют ... char * c; и char *c;
// кажется из назнаний ф-й можно убрать string, struct и array без особой потери ясности, т.к. из названия первого параметра ф-й итак это ясно 
struct lines_storage *divide_string		(char *your_string, char *special_symbols, struct lines_storage *output);
void destroy_struct		(struct lines_storage * line);
struct lines_storage *create_struct		();
void fill_array		(char * input_string, char * symbols);


int main() {
	int i = 0;
	struct lines_storage * date = NULL;
	char input_string[MAX_STRING_SIZE] = {0};
	char delimitors[MAX_DELIMITER_NUMBER] = {0};
	fill_array(input_string, delimitors);
	date = divide_string(input_string, delimitors, date);
	printf("\nYour strings: \n");
	for (i = 0; i < date->number_of_lines; i++) {
		assert(date->lines[i]);
		printf("%s\n", date->lines[i]);
	}
	printf("The number of strings: %lu\n", date->number_of_lines);
	destroy_struct(date);
	return 0;
}



void fill_array(char * input_string, char * symbols) {
	int i = -1;
	printf("Enter your string, use \\n to complete the line input:\n");
	// FIXIT: вы написали свою fgets. Давайте готовой ф-ей воспользуемся
	do {
		i++;
		if (i >= MAX_STRING_SIZE) {
			printf("Too big string\n");
			exit(1);
		}
		input_string[i] = getchar();
	} while (input_string[i] != '\n');
	input_string[i] = '\0';
	i = -1;
	printf("Enter your tokens, use \\n to complete the line input:\n");
	do {
		i++;
		if (i >= MAX_DELIMITER_NUMBER) {
			printf("Too big number of delemitors\n");
			exit(2);
		}
		symbols[i] = getchar();
	} while (symbols[i] != '\n');
	symbols[i] = '\0';
}

struct lines_storage *divide_string(char *your_string, char *special_symbols, struct lines_storage *output) {
	// FIXIT: последний параметр не нужно передавать в ф-ю. вы же явно главное проверяется, что именно NULL передали на вход, и в итоге с помощью return эту структуру возвращается :)
	assert(!output);
	output = create_struct();
	// FIXIT: вы лишний раз прибавили 1, а потом везде вычитаете её. может просто не прибавлять изначатьно?
	output->number_of_lines++;
	output->lines[output->number_of_lines - 1] = strtok(your_string, special_symbols);
	while (output->lines[output->number_of_lines - 1] != NULL) {
		output->number_of_lines++;
		output->lines[output->number_of_lines - 1] = strtok(NULL, special_symbols);
	}
	output->number_of_lines--;
	return output;
}

void destroy_struct(struct lines_storage *line) {
	free(line->lines);
	free(line);
}

struct lines_storage *create_struct() {
	struct lines_storage * output = NULL;
	output = (struct lines_storage *)calloc(1, sizeof(struct lines_storage));
	output->lines = (char**)calloc(MAX_LINES_NUMBER, sizeof(char*));
	return output;
}
