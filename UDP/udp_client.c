#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

void send_mes(char *sendline, struct sockaddr_in servaddr, int sockfd);
void introduce_youself(char *sendline, struct sockaddr_in servaddr, int sockfd);
void name_pers_you_wanna_write(char *sendline, struct sockaddr_in servaddr, int sockfd);
void rec_mes(char *recvline, int sockfd);

int main(int argc, char **argv){
	int i = 0;
	int sockfd = 0;
	char recvline[1000] = {0};
	char sendline[1000] = {0};
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
	
	introduce_youself(sendline, servaddr, sockfd);
	name_pers_you_wanna_write(sendline, servaddr, sockfd);
	pid_t pid = fork();
	if(pid) {
		while(1) {
			for(; i < 1000; i++) {
				sendline[i] = '\0';
			}
			fgets(sendline, 1000, stdin);
			send_mes(sendline, servaddr, sockfd);
			if(!strcmp(sendline, "/exit")) break;
		}
	}
	else while(1) rec_mes(recvline, sockfd);
	close(sockfd);
	return 0;
}

void rec_mes(char *recvline, int sockfd) {
	int i = 0;
	recvfrom(sockfd, recvline, 1000, 0, (struct sockaddr *) NULL, NULL);
	for(i = 0; i < 999; i++) {
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
	printf("Please,say your name: ");
	fgets(sendline, 1000, stdin);
	send_mes(sendline, servaddr, sockfd);
	printf("Name of a person you wanna write: ");
}

void name_pers_you_wanna_write(char *sendline, struct sockaddr_in servaddr, int sockfd) {
	fgets(sendline, 1000, stdin);
	send_mes(sendline, servaddr, sockfd);
	printf("Ok, you have access to write to %s. Write /exit to exit the chat\n", sendline);
}
