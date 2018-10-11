#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"
#include "macro.h"
#include "prototypes.h"

struct command_storage * init_storage() {
	struct command_storage *data = NULL;
	data = (struct command_storage*)calloc(1, sizeof(struct command_storage));
	data->lines = (struct instruction_line**)calloc(INSTRUCTION_MAX_SIZE, sizeof(struct instruction_line*));
	data->number_of_commands = 0;
	return data;
}

struct instruction_line *init_instruction() {
	struct instruction_line *data = NULL;
	data = (struct instruction_line*)calloc(1, sizeof(struct instruction_line));
	data->response_time = 0;
	data->instruction = NULL;
	return data;
}

char *read_input() {
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

void destroy_storage(struct command_storage * data) {
	assert(data);
	assert(data->lines);
	int i = 0;
	for(; i < data->number_of_commands; i++) {
		if(data->lines[i]) free(data->lines[i]);
	}
	free(data->lines);
	free(data);
}
