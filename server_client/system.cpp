#include <iostream>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUMBER_OF_PROCESSORS 1
#define SLEEP_TIME 5

using namespace std;


class mymsgbuf {
protected:
	long mtype;
	long composition;
public:
	mymsgbuf() {
		mtype = 0;
		composition = 0;
	}
};

class client_info : public mymsgbuf {
	int first_mult;
	int second_mult;
	pid_t client_pid;
public:
	client_info() {
		first_mult = 0;
		client_pid = 0;
		second_mult = 0;
	}
	void multiply() { composition = first_mult * second_mult; }
	void switch_client_pid_to_type() { mtype = client_pid; }
};


void semaphore_change(int n, int semid);

int main() {
	class client_info info;
	char pathname[]= "client.cpp";
	char pathname_sem[] = "system.cpp";
	key_t key = 0;
	key_t key_sem = 0;
	key = ftok(pathname, 0);
	key_sem = ftok(pathname_sem, 0);
	int msqid = msgget(key, 0666 | IPC_CREAT);
	int semid = semget(key_sem, 1, 0666 | IPC_CREAT);
	while(1) {
		msgrcv(msqid, &info, sizeof(class client_info) - sizeof(long), 1, 0);
		semaphore_change(1, semid);
		pid_t pid = fork();
		if(!pid) {
			info.multiply();
			info.switch_client_pid_to_type();
			sleep(SLEEP_TIME);
			msgsnd(msqid, &info, sizeof(class client_info) - sizeof(long), 0);
			semaphore_change(-1, semid);
			exit(0);
		}
		//fprintf(stderr, "%d\n", semctl(semid, 0, GETVAL));
		while(semctl(semid, 0, GETVAL) == MAX_NUMBER_OF_PROCESSORS);						//Wait, if system can't create new proccess.
	}
}

void semaphore_change(int n, int semid) {
	struct sembuf sem;
	sem.sem_op = n;
	sem.sem_flg = 0;
	sem.sem_num = 0;
	if(semop(semid, &sem, 1) < 0) perror("semaphore");
}

