#include "prototypes_useless.h"

struct List * list_init() {
	struct List * date = NULL;
	date = (struct List *)calloc(1, sizeof(struct List));
	date->lines = (struct Command **)calloc(100, sizeof(struct Command *));
	date->number_of_commands = 0;
	return date;
}

struct Command * command_init() {
	struct Command * date = NULL;
	date = (struct Command *)calloc(1, sizeof(struct List));
	date->response_time = 0;
	date->instruction = NULL;
	return date;
}

char * load_file() {
	char * strings = (char*)calloc(10000, sizeof(char));
	FILE * f_in = NULL;
	f_in = fopen("command_file", "r");
	if(!f_in) {
		perror("f_in");
		exit(1);
	}
	arr_fill(f_in, strings);
	fclose(f_in);
	return strings;
}

void arr_fill(FILE * stream, char * array) {
	assert(array);
	assert(stream);
	int counter = 0;
	int symbol = 0;
	for(; ; counter++)
	{
		assert(counter < 9990);
		symbol = fgetc(stream);
		if(symbol == EOF) break;
		array[counter] = symbol;
	}
}

void list_destroy(struct List * list) {
	assert(list);
	assert(list->lines);
	int counter = 0;
	for(; counter < list->number_of_commands; counter++) {
		printf("kek");
		free(list->lines[counter]);
	}
	free(list->lines);
	free(list);
}
