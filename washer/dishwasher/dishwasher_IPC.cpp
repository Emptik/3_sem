#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "dishwasher.h"
#include "../macro.h"
#include "../message_object.h"

void wash(int time, char *name) {
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
		perror("semaphore_dishwasher");
		exit(21);
	}
}
	
void dishwasher_interact(class dishwasher *all_dishes) {
	char pathname[]= "../macro.h";
	char pathname_sem[] = "../message_object.h";
	key_t key = 0;
	key_t key_sem = 0;
	
	key = ftok(pathname, 0);
	if(key < 0) {
		perror("key_queue_dishwasher");
		exit(22);
	}
	key_sem = ftok(pathname_sem, 0);
	if(key_sem < 0) {
		perror("key_sem_dishwasher");
		exit(23);
	}
	
	int msqid = msgget(key, 0666 | IPC_CREAT);
	if(msqid < 0) {
		perror("msqid_dishwasher");
		exit(24);
	}
	int semid = semget(key_sem, 1, 0666 | IPC_CREAT);
	if(semid < 0) {
		perror("semid_dishwasher");
		exit(25);
	}
	
	class message mes[QUANTITY_OF_DISH_TYPES] = {};
	int message_number = 0;
	int time = 0;
	
	for(int i = 0; i < QUANTITY_OF_DISH_TYPES; i++) {
		
		mes[i] = message(all_dishes[i].get_dish_type());
		time = all_dishes[i].get_wash_time();
		int number = all_dishes[i].get_number_of_dishes();
		
		for(int j = 0; j < number; j++) {
			wash(time, all_dishes[i].get_dish_type());
			semaphore_change(semid, 1);
			while(semctl(semid, 0, GETVAL) == TABLE_LIMIT);
			msgsnd(msqid, &mes[i], sizeof(class message) - sizeof(long), 0);
		}
		
		message_number++;
	}
}
