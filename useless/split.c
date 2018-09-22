#include "prototypes_useless.h"

struct List * split(struct List * output, char * array) {
	assert(!output); 
	int array_lenght = 0;
	int counter= 0;
	output = list_init();
	assert(output);
	for(; array[counter] != '\0'; counter++) {
		if(array[counter] == '\t') array[counter] = '\0';
	}
	array_lenght = counter;
	for(counter = 0; counter < array_lenght; counter++) {
		output->lines[output->number_of_commands] = command_init();
		output->lines[output->number_of_commands]->response_time = atoi(array + counter);
		for(; array[counter] != '\0'; counter++);
		counter++;
		output->lines[output->number_of_commands]->instruction = array + counter;
		for(; array[counter] != '\n'; counter++);
		array[counter] = '\0';
		counter++;
		output->number_of_commands++;
	}
	return output;
}
