#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define AMOUNT_OF_DATA 100000000
#undef RAND_MAX 
#define RAND_MAX 100
#define NUMBER_OF_THREADS 10
#define NO_THREADS 0

struct thread_info

struct thread_arguments {
	int * start;
};

//void create_data(int * array);
//void * thread_calculate(void * arg);

void calculate(int number_of_threads, int *data);

int main() {
	int status;
	int *data = calloc(AMOUNT_OF_DATA, sizeof(int));
	create_data(data);
	pid_t no_threads = fork();
	if(!no_threads) calculate(NO_THREADS, data);
	wait(&status);
	pid_t proc_with_threads = fork();
	if(!no_threads) calculate(NUMBER_OF_THREADS, data);
	wait(&status);
	free(data);
	return 0;
}

void create_data(int * array) {
	int i = 0;
	for(; i < AMOUNT_OF_DATA ; i++) {
		//array[i] = rand() % RAND_MAX - RAND_MAX / 2;
		array[i] = 5;
	}
}

void calculate(int number_of_threads, int *data) {
	if(number_of_threads == 0) {
		long long int sum = 0;
		int i = 0;
		for( ; i < AMOUNT_OF_DATA; i++)
	}
/*
void process_work(unsigned int number_of_threads, int * data)
{
	if(number_of_threads < MAX_NUMBER_OF_THREADS) {
		//pid_t pid = fork();
		//if(!pid) {
			//process_work(++number_of_threads, data);
			//exit(number_of_threads);
		//}
		int i = 0;
		int status = 0;
		int sum = 0;
		pthread_t *id_storage = (pthread_t *)calloc(number_of_threads, sizeof(pthread_t));
		//id_storage[0] = 1;
		struct thread_arguments *arg = calloc(1, sizeof(struct thread_arguments));
		arg->number_of_threads = number_of_threads;
		arg->thread_number = 1;
		arg->data = data;
		//wait(&status);
		//printf("%d\n", number_of_threads);
		//for(i = 0; i < number_of_threads; i++) {
			//printf("kek\n");
			int err = pthread_create(&id_storage[i], NULL, &thread_calculate, arg);
			perror("err");
			arg->thread_number ++;
			//printf("kek\n");
		//}
		for(i = 0; i <= number_of_threads; i++) {
			sum += arg->sum[i];
		}
		printf("%d\n", arg->sum[1]);
	}
	exit(1);
}

void * thread_calculate(void * arg) {
	//fprintf(stderr, "kek_2\n");
	int j = 0;
	struct thread_arguments *tinfo = (struct thread_arguments *)arg;
	//printf("%d\n", tinfo->sum[tinfo->thread_number] );
	while(j != AMOUNT_OF_DATA / tinfo->number_of_threads) {
		tinfo->sum[tinfo->thread_number] += *(tinfo->data + (AMOUNT_OF_DATA / tinfo->number_of_threads) * (tinfo->thread_number - 1) + j);
		j++;
	}
	return &tinfo->sum[tinfo->thread_number];
}
*/
