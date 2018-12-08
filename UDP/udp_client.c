#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>    
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE_OF_PREFIX 4
#define MAX_MESSAGE_LENGTH 100
#define RECIEVE_MAX_MESSAGE_LENGTH 200


void send_mes(char *sendline, struct sockaddr_in servaddr, int sockfd);
void introduce_youself(char *sendline, struct sockaddr_in servaddr, int sockfd);
void name_pers_you_wanna_write(char *sendline, struct sockaddr_in servaddr, int sockfd);
void rec_mes(char *recvline, int sockfd);

int main(int argc, char **argv){
	int i = 0;
	int sockfd = 0;
	char recvline[MAX_MESSAGE_LENGTH] = {0};
	char sendline[RECIEVE_MAX_MESSAGE_LENGTH] = {0};
	struct sockaddr_in servaddr, cliaddr;
	if(argc != 2){
		printf("usage: a.out <IP>\n");
		exit(-1);
	}
	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("sockfd");
		exit(-1);
	}
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(0);
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0){
		perror("bind");
		close(sockfd);
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51002);
	if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
		perror("inet_aton");
		close(sockfd);
		exit(1);
	}
	
	pid_t pid = fork();
	if(pid) {
		introduce_youself(sendline, servaddr, sockfd);
		while(1) {
			for(i = 0; i < MAX_MESSAGE_LENGTH; i++) {
				sendline[i] = '\0';
			}
			fgets(sendline, MAX_MESSAGE_LENGTH, stdin);
			send_mes(sendline, servaddr, sockfd);
			if(!strcmp(sendline, "/exit\n")) {
				kill(pid, SIGKILL);
				break;
			}
		}
	}
	else while(1) rec_mes(recvline, sockfd);
	close(sockfd);
	return 0;
}

void rec_mes(char *recvline, int sockfd) {
	int i = 0;
	recvfrom(sockfd, recvline, RECIEVE_MAX_MESSAGE_LENGTH, 0, (struct sockaddr *) NULL, NULL);
	for(i = 0; i < RECIEVE_MAX_MESSAGE_LENGTH - 1; i++) {
		if(recvline[i] == '\n') {
			recvline[i + 1] = '\0';
			break;
		}
	}
	printf("%s", recvline);
}

void send_mes(char *sendline, struct sockaddr_in servaddr, int sockfd) {
	if(sendto(sockfd, sendline, strlen(sendline) + 1, 0 , (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
		perror("sendto");
		exit(1);
	}
}

void introduce_youself(char *sendline, struct sockaddr_in servaddr, int sockfd) {
	printf("Please,say your name:\n");
	fgets(sendline, MAX_MESSAGE_LENGTH, stdin);
	send_mes(sendline, servaddr, sockfd);
	printf("Name of a person you wanna write:\n");
}

void name_pers_you_wanna_write(char *sendline, struct sockaddr_in servaddr, int sockfd) {
	fgets(sendline, MAX_MESSAGE_LENGTH, stdin);
	send_mes(sendline, servaddr, sockfd);
}
