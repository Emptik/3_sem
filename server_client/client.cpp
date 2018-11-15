#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>

#undef RAND_MAX 
#define RAND_MAX 70
#define PRIORITY 1

using namespace std;



class mymsgbuf {
	long mtype;
protected:
	long composition;
	mymsgbuf() {
		mtype = PRIORITY;
		composition = 0;
	}
};

class client_info : public mymsgbuf {
	int first_mult;
	int second_mult;
	pid_t client_pid;
public:
	int msqid;
	client_info() {
		first_mult = rand() % RAND_MAX - RAND_MAX / 2;
		client_pid = getpid();
		second_mult = rand() % RAND_MAX - RAND_MAX / 2;
	}
	pid_t get_client_pid() { return client_pid; }
	void pull_the_result_out() { 
		cout << "first_mult: " << first_mult << "\nsecond_mult: ";
		cout << second_mult << "\ncomposition: " << composition << endl; 
	}
};



int main() {
	srand(time(NULL));										//Make our values realy random
	class client_info info;
	char pathname[]= "client.cpp";
	key_t key = 0;
	key = ftok(pathname, 0);
	int msqid = msgget(key, 0666 | IPC_CREAT);
	msgsnd(msqid, &info, sizeof(class client_info) - sizeof(long), 0);
	msgrcv(msqid, &info, sizeof(class client_info) - sizeof(long), info.get_client_pid(), 0);
	info.pull_the_result_out();
}

