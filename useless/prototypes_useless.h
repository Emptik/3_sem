#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
 #include <unistd.h>

struct List {
	unsigned int number_of_commands;
	struct Command ** lines;
};

struct Command {
	unsigned int response_time;
	char * instruction;
};

struct List * split(struct List * output, char * array);
struct List * list_init();
struct Command * command_init();
void list_destroy(struct List * list);
void command_destroy(struct Command * command);
char * load_file();
void arr_fill(FILE * stream, char * array);
void dot_print(struct List * strings);
