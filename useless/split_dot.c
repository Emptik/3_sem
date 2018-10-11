#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "manager.h"
#include "prototypes.h"
#include "split.h"

struct command_storage *make_split(char *array_data) {
	char * array_to_intenger[1] = {0};
	struct command_storage * output = init_storage();
	output->lines[output->number_of_commands] = init_instruction();
	array_to_intenger[0] = strtok(array_data, "\t");
	if(*array_to_intenger[0]) output->lines[output->number_of_commands]->response_time = atoi(array_to_intenger[0]);
	output->lines[output->number_of_commands]->instruction = strtok(NULL, "\n");
	
	while (output->lines[output->number_of_commands]->instruction != NULL) {
		output->number_of_commands++;
		output->lines[output->number_of_commands] = init_instruction();
		array_to_intenger[0] = strtok(NULL, "\t");
		if(*array_to_intenger[0]) output->lines[output->number_of_commands]->response_time = atoi(array_to_intenger[0]);
		output->lines[output->number_of_commands]->instruction = strtok(NULL, "\n");
	}
	
	free(output->lines[output->number_of_commands]);
	return output;
}

// The function makes a dot file. Don't use it if you do not have the Graphviz.
void dot_print(struct command_storage * strings) {
	assert(strings);
	int i = 0;
	int j = 0;
	FILE * stream = fopen("pic.dot", "w+");
	if(!stream) {
		perror("stream");
		exit(2);
	}
	fprintf(stream, "digraph G{\n");
	fprintf(stream, "node [style=filled, color=darkolivegreen1];\n");
	fprintf(stream, "n000 [label=\"\"] ;\n");
	for(; i  < strings->number_of_commands; i++) {
		fprintf(stream, "n000 -> n%03d;\n", ++j);
		fprintf(stream, "n%03d [label=\"%d\"] ;\n", j, strings->lines[i]->response_time);
		fprintf(stream, "n000 -> n%03d;\n", ++j);
		fprintf(stream, "n%03d [label=\"%s\"] ;\n", j, strings->lines[i]->instruction);
		fprintf(stream, "n%03d -> n%03d;\n", j, j - 1);
		fprintf(stream, "n%03d -> n%03d;\n", j - 1, j);
	}
	fprintf(stream, "\n}");
	fclose(stream);
}
