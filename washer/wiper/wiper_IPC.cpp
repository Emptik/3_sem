#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "wiper.h"
#include "../macro.h"
#include "../message_object.h"

void wipe(int time, char *name) {
	int i = 0;
	for(i = 0; i < time; i++);
	fprintf(stderr, "A dish named '%s' is succefuly washed for %d tacts\n", name, i);
}

void semaphore_change(int semid, int n) {
	struct sembuf sem;
	sem.sem_op = n;
	sem.sem_flg = 0;
	sem.sem_num = 0;
	if(semop(semid, &sem, 1) < 0) {
		perror("semaphore_wiper");
		exit(11);
	}
}

void wiper_interact(class wiper *all_dishes) {
	char pathname[]= "../macro.h";
	char pathname_sem[] = "../message_object.h";
	key_t key = 0;
	key_t key_sem = 0;
	
	key = ftok(pathname, 0);
	if(key < 0) {
		perror("key_queue_wiper");
		exit(12);
	}
	key_sem = ftok(pathname_sem, 0);
	if(key_sem < 0) {
		perror("key_sem_wiper");
		exit(13);
	}
	
	int msqid = msgget(key, 0666 | IPC_CREAT);
	if(msqid < 0) {
		perror("msqid_wiper");
		exit(14);
	}
	int semid = semget(key_sem, 1, 0666 | IPC_CREAT);
	if(semid < 0) {
		perror("semid_wiper");
		exit(15);
	}
	
	class message mes;
	while(1) {
		msgrcv(msqid, &mes, sizeof(class message) - sizeof(long), 1, 0);
		for(int i = 0; i < QUANTITY_OF_DISH_TYPES; i++) {
			if(strcmp(mes.get_dish(), all_dishes[i].get_dish_type()) == 0) {
				wipe(all_dishes[i].get_wipe_time(), all_dishes[i].get_dish_type());
				semaphore_change(semid, -1);
				break;
			}
		}
	}
}
