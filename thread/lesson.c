#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define AMOUNT_OF_DATA 100000000
#undef RAND_MAX
#define RAND_MAX 100000000
#define MAX_NUMBER_OF_THREADS 10

struct thread_arguments {
	unsigned int number_of_threads;
	unsigned int thread_number;
};

void create_data(int * array);
void process_work(unsigned int number_of_threads, int * data);
void * thread_calculate(void * arg);

int main() {
	int status = 0;
	unsigned int number_of_threads = 1;
	int * data = (int*)calloc(AMOUNT_OF_DATA, sizeof(int));
	create_data(data);
	pid_t pid = fork();
	if(!pid) process_work(number_of_threads, data);
	wait(&status);
	return 0;
}

void create_data(int * array) {
	int i = 0;
	for(; i < AMOUNT_OF_DATA ; i++) {
		array[i] = rand() % RAND_MAX - RAND_MAX / 2;
	}
}

void process_work(unsigned int number_of_threads, int * data)
{
	if(number_of_threads < MAX_NUMBER_OF_THREADS) {
		pid_t pid = fork();
		if(!pid) {
			process_work(++number_of_threads, data);
			exit(number_of_threads);
		}
		int i = 0;
		int status = 0;
		pthread_t *id_storage = (pthread_t *)calloc(number_of_threads, sizeof(pthread_t));
		struct thread_arguments *arg = calloc(1, sizeof(struct thread_arguments));
		arg->number_of_threads = number_of_threads;
		arg->thread_number = 1;
		wait(&status);
		//printf("%d\n", number_of_threads);
		for(; i <= number_of_threads; i++) {
			pthread_create(&id_storage[i], NULL, thread_calculate, arg);
		}
	}
}

void * thread_calculate(void * arg) {
	;
}
