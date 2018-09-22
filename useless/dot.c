#include "prototypes_useless.h"

void dot_print(struct List * strings) {
	assert(strings);
	int counter_1 = 0;
	int counter_2 = 0;
	int strings_remember = 0;
	FILE * stream = fopen("pic.dot", "w+");
	if(!stream) {
		perror("stream");
		exit(2);
	}
	fprintf(stream, "digraph G{\n");
	fprintf(stream, "node [style=filled, color=darkolivegreen1];\n");
	fprintf(stream, "n000 [label=\"\"] ;\n");
	for(; strings->lines[counter_1] != NULL; counter_1++) {
		fprintf(stream, "n000 -> n%03d;\n", ++counter_2);
		fprintf(stream, "n%03d [label=\"%d\"] ;\n", counter_2, strings->lines[counter_1]->response_time);
		fprintf(stream, "n000 -> n%03d;\n", ++counter_2);
		fprintf(stream, "n%03d [label=\"%s\"] ;\n", counter_2, strings->lines[counter_1]->instruction);
		fprintf(stream, "n%03d -> n%03d;\n", counter_2, counter_2 - 1);
		fprintf(stream, "n%03d -> n%03d;\n", counter_2 - 1, counter_2);
	}
	fprintf(stream, "\n}");
	fclose(stream);
}
