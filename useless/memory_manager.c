#include "prototypes.h"

struct command_storage * init_storage() {
	// data?
	struct command_storage *date = NULL;
	date = (struct command_storage*)calloc(1, sizeof(struct command_storage));
	// FIXIT: 100 нужно вынести в отдельную константу
	// можно хотя бы строкой выше написать const int ... = 100;
	date->lines = (struct instruction_line**)calloc(100, sizeof(struct instruction_line*));
	date->number_of_commands = 0;
	return date;
}

struct instruction_line *init_instruction() {
	struct instruction_line *date = NULL;
	date = (struct instruction_line*)calloc(1, sizeof(struct instruction_line));
	date->response_time = 0;
	date->instruction = NULL;
	return date;
}

char *fill_arr() {
	char * input_string = calloc(STRING_MAX_SIZE, sizeof(char));
	int i = -1;
	do {
		i++;
		if (i >= STRING_MAX_SIZE) {
			printf("Too big string\n");
			exit(1);
		}
		input_string[i] = getchar();
	} while (input_string[i] != EOF);
	input_string[i] = '\0';
	return input_string;
}

void destroy_storage(struct command_storage * date) {
	assert(date);
	assert(date->lines);
	int i = 0;
	for(; i < date->number_of_commands; i++) {
		if(date->lines[i]) free(date->lines[i]);
	}
	free(date->lines);
	free(date);
}
