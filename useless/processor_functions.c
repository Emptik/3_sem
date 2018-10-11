#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include "macro.h"
#include "prototypes.h"
#include "processor.h"

void do_instruction(struct instruction_line *command) {
	int i = 0;
	char * argv[MAX_NUMBER_OF_ARGUMENTS] = {0};
	argv[0] = strtok(command->instruction, " ");
	do {
		i++;
		argv[i] = strtok(NULL, " ");
	} while (argv[i] != NULL);
	sleep(command->response_time);
	execvp(argv[0], argv);
	exit(1);
}

void kill_process(pid_t pid, unsigned int instruction_time,unsigned int time_out) {
	sleep(time_out + instruction_time);
	kill(pid, SIGKILL);
	exit(2);
}

void do_all_instructions(struct command_storage *my_struct, unsigned int time_out) {
	int i = 0;
	pid_t worker_pid = 0;
	pid_t sleeper_pid = 0;
	for( ; i < my_struct->number_of_commands; i++) {
		worker_pid = fork();
		if(!worker_pid) do_instruction(my_struct->lines[i]);
		sleeper_pid = fork();
		if(!sleeper_pid) { 
			kill_process(worker_pid, my_struct->lines[i]->response_time, time_out);
		}
	}
}
