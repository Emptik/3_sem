#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/signal.h>

#define STRING_MAX_SIZE 5000
#define MAX_NUMBER_OF_ARGUMENTS 100

struct command_storage {
	size_t number_of_commands;
	struct instruction_line ** lines;
};

struct instruction_line {
	size_t response_time;
	char * instruction;
};

int time_out;

struct command_storage *init_storage();
struct instruction_line *init_instruction();
void destroy_storage(struct command_storage *pack);
void destroy_instruction(struct instruction_line *command);
char *fill_arr();

struct command_storage *make_split(struct command_storage *output, char *array_data);
void dot_print(struct command_storage * strings);

void work(struct command_storage * my_struct);
void do_instruction(struct instruction_line * command);
void kill_process(size_t *pid, size_t instruction_time);
