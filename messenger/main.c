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

void client_work(int *fd, char *input, char *output, int pid);

int main(int argc, char *argv[], char *envp[]) {
	int fd[2] = {0};
	char input[ARRAY_SIZE] = {0};
	char output[ARRAY_SIZE] = {0};
	pid_t pid = 0;
	mkfifo("1_client_input", 0777);
	mkfifo("2_client_input", 0777);
	
	// FIXIT: кажется, что одного fork вполне достаточно. и как раз пропадут сложные логические выражения с !print_pid и !pid
	// Еще теоретически для сокращения объема кода может быть удобен тернарный оператор условие ? выражение1 : выражение2
	pid = fork();
	if(atoi(argv[1]) == FIRST_CLIENT) {
		(!pid) ? (fd[1] = open("1_client_input", O_WRONLY)) : (fd[0] = open("2_client_input", O_RDONLY));
		while(1) {
			client_work(fd, input, output, pid);
		}
	}
	if(atoi(argv[1]) == SECOND_CLIENT) {
		(!pid) ? (fd[1] = open("2_client_input", O_WRONLY)) : (fd[0] = open("1_client_input", O_RDONLY));
		while(1) {
			client_work(fd, input, output, pid);
		}
	}
	return 0;
}

void client_work(int *fd, char *input, char *output, int pid) {
	if(!pid) {
		fgets(input, MAX_MESSAGE_SIZE, stdin);
		write(fd[1], input, MAX_MESSAGE_SIZE);
	}
	else {
		read(fd[0], output, MAX_MESSAGE_SIZE);
		fprintf(stdout, "%s", output);
	}
}
