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

enum client_const {
	NO_EXIST = -1,
	NO_NAMED
};

struct client {
	char client_name[100];
	char client_to_write[100];
	struct sockaddr_in cliaddr;
	struct sockaddr_in writeaddr;
};

struct sockaddr_in create_servaddr();
void make_socket(int *sockfd, struct sockaddr_in servaddr);
int is_client_port_exist(int num_of_prs, struct sockaddr_in swap, struct client **chat);
void create_client(struct client **chat, int *num_of_prs, struct sockaddr_in swap, char *message);
int is_client_named_his_partner(struct client **chat, int existing_client);
void find_a_partner(struct client **chat, char *message, int existing_client, int num_of_prs);



int main(){
	struct sockaddr_in swap;
	int sockfd = 0;
	int num_of_prs = 0;
	unsigned int clilen = 0;
	char message[100] = {0};
	
	struct sockaddr_in servaddr = create_servaddr();
	make_socket(&sockfd, servaddr);
	
	struct client **chat = calloc(1, sizeof(struct client*));
	chat[num_of_prs] = calloc(1, sizeof(struct client));
	while(1){
		clilen = sizeof(chat[0]->cliaddr);
		if (recvfrom(sockfd, message, 999, 0, (struct sockaddr *) &swap, &clilen)<0){
			perror("recvfrom");
			close(sockfd);
			exit(-1);
		}
		
		int existing_client = is_client_port_exist(num_of_prs, swap, chat);
		if(existing_client == NO_EXIST) {
			create_client(chat, &num_of_prs, swap, message);
		}
		else if(is_client_named_his_partner(chat, existing_client) == NO_NAMED) {
			find_a_partner(chat, message, existing_client, num_of_prs);
		}
		else {
			if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *) &(chat[existing_client]->writeaddr), clilen)<0){
				perror("sendto");
				close(sockfd);
				exit(-1);
			}
		}
	}
	return 0;
}

void find_a_partner(struct client **chat, char *message, int existing_client, int num_of_prs) {
	int i = 0;
	assert(chat[num_of_prs]->client_to_write);
	strcpy(chat[existing_client]->client_to_write, message);
	for(; i < num_of_prs; i++) {
		if(chat[i]) {
			if(!strcmp(chat[existing_client]->client_to_write, chat[i]->client_name)) {
				chat[existing_client]->writeaddr.sin_port = chat[i]->cliaddr.sin_port;
				chat[existing_client]->writeaddr.sin_family = chat[i]->cliaddr.sin_family;
				chat[existing_client]->writeaddr.sin_addr.s_addr = chat[i]->cliaddr.sin_addr.s_addr;
				return ;
			}
		}
	}
	printf("%s", chat[existing_client]->client_to_write);
};

void create_client(struct client **chat, int *num_of_prs, struct sockaddr_in swap, char *message) {
	chat[*num_of_prs] = calloc(1, sizeof(struct client));
	chat[*num_of_prs]->cliaddr.sin_port = swap.sin_port;
	chat[*num_of_prs]->cliaddr.sin_family = swap.sin_family;
	chat[*num_of_prs]->cliaddr.sin_addr.s_addr = swap.sin_addr.s_addr;
	strcpy(chat[*num_of_prs]->client_name, message);
	(*num_of_prs)++;
}

int is_client_named_his_partner(struct client **chat, int existing_client) {
	if(chat[existing_client]->client_to_write[0] == '\0') return NO_NAMED;
	else return 1;
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
