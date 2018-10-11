#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define FIRST_CLIENT 0
#define SECOND_CLIENT 1
#define MAX_MESSAGE_SIZE 100
#define ARRAY_SIZE 1000

int main(int argc, char *argv[], char *envp[]) {
	int fd[2] = {0};
	char input[ARRAY_SIZE] = {0};
	char output[ARRAY_SIZE] = {0};
	pid_t write_pid = 0;
	pid_t print_pid = 0;
	mkfifo("1_client_input", 0777);
	mkfifo("2_client_input", 0777);
	write_pid = fork();
	if(write_pid) print_pid = fork();
	if(atoi(argv[1]) == FIRST_CLIENT) {
		if(!write_pid) fd[1] = open("1_client_input", O_WRONLY);
		if(!print_pid && write_pid) fd[0] = open("2_client_input", O_RDONLY);
		while(1) {
			if(!write_pid && !print_pid) {
				fgets(input, MAX_MESSAGE_SIZE, stdin);
				write(fd[1], input, MAX_MESSAGE_SIZE);
			}
			if(!print_pid && write_pid) {
				read(fd[0], output, MAX_MESSAGE_SIZE);
				fprintf(stdout, "%s", output);
			}
		}
	}
	if(atoi(argv[1])== SECOND_CLIENT) {
		if(!write_pid) fd[1] = open("2_client_input", O_WRONLY);
		if(!print_pid && write_pid) fd[0] = open("1_client_input", O_RDONLY);
		while(1) {
			if(!write_pid && !print_pid) {
				fgets(input, MAX_MESSAGE_SIZE, stdin);
				write(fd[1], input, MAX_MESSAGE_SIZE);
			}
			if(!print_pid && write_pid) {
				read(fd[0], output, MAX_MESSAGE_SIZE);
				fprintf(stdout, "%s", output);
			}
		}
	}
	return 0;
}
