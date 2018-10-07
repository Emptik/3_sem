#include "prototypes.h"

void work(struct command_storage * my_struct) {
	int i = 0;
	// лучше использовать pid_t для worker_pid и sleeper_pid
	size_t worker_pid = 0;
	size_t sleeper_pid = 0;
	for( ; i < my_struct->number_of_commands; i++) {
		worker_pid = fork();
		if(!worker_pid) do_instruction(my_struct->lines[i]);
		// На самом деле, если exec не смог запуститься, то дочерний процесс дальше продолжит существовать и пытаться какого тоже запускать
		// Советую попробовать добавить в начало списка команд несколько несуществующих
		sleeper_pid = fork();
		if(!sleeper_pid) { 
			kill_process(&worker_pid, my_struct->lines[i]->response_time);
		}
	}
}

void do_instruction(struct instruction_line * command) {
	int i = 0;
	// Давайте уберем _ из названия. Его не соответствует стилю кода.
	char * argv_[MAX_NUMBER_OF_ARGUMENTS] = {0};
	argv_[0] = strtok(command->instruction, " ");
	do {
		i++;
		argv_[i] = strtok(NULL, " ");
	} while (argv_[i] != NULL);
	sleep(command->response_time);
	// Я не до конца понимаю, зачем сначала execlp вызывать, а потом, если что-то пошло не так, то execvp.
	// Напишите комментарий, пожалуйста, к этому действию.
	if(!argv_[0]) execlp(argv_[0], "");
	execvp(argv_[0], argv_);
}

// FIXIT: нет смысла передавать pid по указателю
void kill_process(size_t *pid, size_t instruction_time) {
	sleep(time_out + instruction_time);
	// Лучше вместо числа 9 написать SIGKILL
	kill(*pid, 9);
	exit(2);
}
