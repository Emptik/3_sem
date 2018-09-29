#include "prototypes.h"

void work(struct command_storage * my_struct) {
	int i = 0;
	size_t worker_pid = 0;
	size_t sleeper_pid = 0;
	for( ; i < my_struct->number_of_commands; i++) {
		worker_pid = fork();
		if(!worker_pid) do_instruction(my_struct->lines[i]);
		sleeper_pid = fork();
		if(!sleeper_pid) { 
			kill_process(&worker_pid, my_struct->lines[i]->response_time);
		}
	}
}

void do_instruction(struct instruction_line * command) {
	int i = 0;
	char * argv_[MAX_NUMBER_OF_ARGUMENTS] = {0};
	argv_[0] = strtok(command->instruction, " ");
	do {
		i++;
		argv_[i] = strtok(NULL, " ");
	} while (argv_[i] != NULL);
	sleep(command->response_time);
	if(!argv_[0]) execlp(argv_[0], "");
	execvp(argv_[0], argv_);
}


void kill_process(size_t *pid, size_t instruction_time) {
	sleep(time_out + instruction_time);
	kill(*pid, 9);
	exit(2);
}
