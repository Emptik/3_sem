#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define MES_TO_ALL 8
#define MAX_MESSAGE_LENGTH 100
#define MAX_SEND_MESSAGE_LENGTH 200

enum client_const {
	NO_EXIST = -1,
	NO_NAMED,
	NAMED
};

struct client {
	char client_name[MAX_MESSAGE_LENGTH];
	char client_to_write[MAX_MESSAGE_LENGTH];
	struct sockaddr_in cliaddr;
	struct sockaddr_in writeaddr;
};

struct sockaddr_in create_servaddr();
void make_socket(int *sockfd, struct sockaddr_in servaddr);
int is_client_port_exist(int num_of_prs, struct sockaddr_in swap, struct client **chat);
void create_client(struct client **chat, int *num_of_prs, struct sockaddr_in swap, char *message);
int is_client_named_his_partner(struct client **chat, int current_client);
void find_a_partner(struct client **chat, char *message, int current_client, int num_of_prs, int sockfd, unsigned int clilen);
void send_email(struct client **chat, char *message, int current_client, int sockfd, int num_of_prs, int clilen);
int is_mes_to_all(char *message);


int main(){
	struct sockaddr_in swap;
	int sockfd = 0;
	int num_of_prs = 0;
	unsigned int clilen = 0;
	char message[MAX_MESSAGE_LENGTH] = {0};
	
	struct sockaddr_in servaddr = create_servaddr();
	make_socket(&sockfd, servaddr);
	
	struct client **chat = calloc(1, sizeof(struct client*));
	chat[num_of_prs] = calloc(1, sizeof(struct client));
	while(1){
		clilen = sizeof(chat[0]->cliaddr);
		if (recvfrom(sockfd, message, MAX_MESSAGE_LENGTH - 1, 0, (struct sockaddr *) &swap, &clilen)<0){
			perror("recvfrom");
			close(sockfd);
			exit(-1);
		}
		
		int current_client = is_client_port_exist(num_of_prs, swap, chat);
		if(current_client == NO_EXIST) {
			create_client(chat, &num_of_prs, swap, message);
		}
		else if(is_client_named_his_partner(chat, current_client) == NO_NAMED) {
			find_a_partner(chat, message, current_client, num_of_prs, sockfd, clilen);
		}
		else send_email(chat, message, current_client, sockfd, num_of_prs, clilen);
	}
	return 0;
}

void send_email(struct client **chat, char *message, int current_client, int sockfd, int num_of_prs, int clilen) {
	int i = 0;
	if(strcmp(message, "/exit\n")) {
		if(is_mes_to_all(message)) {
			char writer_with_message[MAX_SEND_MESSAGE_LENGTH] = {0};
			for(i = 0; i < MAX_MESSAGE_LENGTH && chat[current_client]->client_name[i] != '\n'; i++) {
				writer_with_message[i] = chat[current_client]->client_name[i];
			}
			writer_with_message[i]= '\0';
			strcat(writer_with_message, ":");
			strcat(writer_with_message, message);
			for(i = 0; i < num_of_prs; i++) {
				if(chat[i]) {
					if (sendto(sockfd, writer_with_message, strlen(writer_with_message), 0, (struct sockaddr *) &(chat[i]->cliaddr), clilen)<0){
						printf("pers_num = %d\n", i);
						perror("sendto mes all");
						close(sockfd);
						exit(-15);
					}
				}
			}
		}
		else {	
			char writer_with_message[MAX_SEND_MESSAGE_LENGTH] = {0};
			for(i = 0; i < MAX_MESSAGE_LENGTH && chat[current_client]->client_name[i] != '\n'; i++) {
				writer_with_message[i] = chat[current_client]->client_name[i];
			}
			writer_with_message[i]= '\0';
			strcat(writer_with_message, ":");
			strcat(writer_with_message, message);
			if (sendto(sockfd, writer_with_message, strlen(writer_with_message), 0, (struct sockaddr *) &(chat[current_client]->writeaddr), clilen)<0){
				perror("sendto mes");
				close(sockfd);
				exit(-15);
			}
		}
	}
	else if(strcmp(message, "/exit\n") == 0) {
		char leave_mes[MAX_SEND_MESSAGE_LENGTH] = {0};
		strcpy(leave_mes, "Oh, your partner leave the chat. You can find an another one or write /exit\n");
		if (sendto(sockfd, leave_mes, strlen(leave_mes), 0, (struct sockaddr *) &(chat[current_client]->writeaddr), clilen)<0){
			perror("sendto mes");
			close(sockfd);
			exit(-15);
		}
		for(; i < num_of_prs; i++) {
			if(chat[i]) {
				if(!strcmp(chat[current_client]->client_name, chat[i]->client_to_write)) break;
			}
		}
		if(i != num_of_prs) {
			bzero(chat[i]->client_to_write, MAX_MESSAGE_LENGTH);
			bzero(&chat[i]->writeaddr, sizeof(chat[i]->writeaddr));
			free(chat[current_client]);
		}
	}
}

int is_mes_to_all(char *message) {
	int i = 0;
	char to_all[MES_TO_ALL + 1] = {0};
	for(; i < MES_TO_ALL; i++) {
		to_all[i] = message[i];
	}
	to_all[i] = '\0';
	if(!strcmp(to_all, "TO_ALL: ")) return 1;
	else return 0;
}
	

void find_a_partner(struct client **chat, char *message, int current_client, int num_of_prs, int sockfd, unsigned int clilen) {
	char status_message[MAX_MESSAGE_LENGTH] = {0};
	int i = 0;
	assert(chat[num_of_prs]->client_to_write);
	strcpy(chat[current_client]->client_to_write, message);
	for(; i < num_of_prs; i++) {
		if(chat[i]) {
			if(!strcmp(chat[current_client]->client_to_write, chat[i]->client_name)) {
				chat[current_client]->writeaddr.sin_port = chat[i]->cliaddr.sin_port;
				chat[current_client]->writeaddr.sin_family = chat[i]->cliaddr.sin_family;
				chat[current_client]->writeaddr.sin_addr.s_addr = chat[i]->cliaddr.sin_addr.s_addr;
				strcpy(status_message, "Ok, you have an access to write to. Write /exit to exit the chat.\n");
				if (sendto(sockfd, status_message, strlen(status_message), 0, (struct sockaddr *) &(chat[current_client]->cliaddr), clilen)<0){
					perror("sendto");
					close(sockfd);
					exit(-1);
				}
				return ;
			}
		}
	}
	for(i = 0; i < MAX_MESSAGE_LENGTH; i++) {
		chat[current_client]->client_to_write[i] = '\0';
	}
	strcpy(status_message, "Sorry, there is no such client in the chat. Try to write to an another person:\n");
	if (sendto(sockfd, status_message, strlen(status_message), 0, (struct sockaddr *) &(chat[current_client]->cliaddr), clilen)<0){
		perror("sendto");
		close(sockfd);
		exit(-1);
	}
};

void create_client(struct client **chat, int *num_of_prs, struct sockaddr_in swap, char *message) {
	chat[*num_of_prs] = calloc(1, sizeof(struct client));
	chat[*num_of_prs]->cliaddr.sin_port = swap.sin_port;
	chat[*num_of_prs]->cliaddr.sin_family = swap.sin_family;
	chat[*num_of_prs]->cliaddr.sin_addr.s_addr = swap.sin_addr.s_addr;
	strcpy(chat[*num_of_prs]->client_name, message);
	(*num_of_prs)++;
}

int is_client_named_his_partner(struct client **chat, int current_client) {
	if(chat[current_client]->client_to_write[0] == '\0') return NO_NAMED;
	else return NAMED;
}

int is_client_port_exist(int num_of_prs, struct sockaddr_in swap, struct client **chat) {
	int i = 0;
	for(; i < num_of_prs; i++) {
		if(chat[i]) {
			if(swap.sin_port == chat[i]->cliaddr.sin_port) return i;
		}
	}
	return NO_EXIST;
};
 
struct sockaddr_in create_servaddr() {
	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(51002);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	return server;
}

void make_socket(int *sockfd, struct sockaddr_in servaddr) {
	if ((*sockfd = socket(PF_INET, SOCK_DGRAM, 0))<0) {
		perror("sockfd");
		exit(1);
	}
	if (bind(*sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
		perror("bind");
		close(*sockfd);
		exit(2);
	}
}
