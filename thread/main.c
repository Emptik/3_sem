#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define AMOUNT_OF_DATA 100000000
#undef RAND_MAX 
#define RAND_MAX 50
#define SEVERAL_THREADS 10
#define NO_THREADS 0

struct thread_info {
	pthread_t th_mark; 
	int *start;
	int addend; 					//The quantity of numbers to count in a thread.
	struct mean_variance *values;
};

struct mean_variance {
	double average;
	double dispersion;
};

struct mean_variance calculate(int number_of_threads, int *data);
void *thread_work(void * arg);
void create_data(int * array);

int main() {
	int *data = calloc(AMOUNT_OF_DATA, sizeof(int));
	struct mean_variance val_no_thr = {0, 0};
	struct mean_variance val = {0, 0};
	create_data(data);
	val_no_thr = calculate(NO_THREADS, data);
	val = calculate(SEVERAL_THREADS, data);
	printf("\nNo_threads\nAverage value: %f\nDispersion: %f\n", val_no_thr.average, val_no_thr.dispersion);
	printf("\nSeveral_threads\nAverage value: %f\nDispersion: %f\n", val.average, val.dispersion);
	//int i = 0;
	//for(; i < AMOUNT_OF_DATA; i++) printf("%d\n", data[i]);
	free(data);
	return 0;
}

void create_data(int * array) {
	int i = 0;
	for(; i < AMOUNT_OF_DATA; i++) {
		array[i] = rand() % RAND_MAX - RAND_MAX / 2;
	}
}

struct mean_variance calculate(int number_of_threads, int *data) {
	if(!number_of_threads) {
		struct mean_variance value = {0, 0};
		double sum = 0;
		int i = 0;
		for( ; i < AMOUNT_OF_DATA; i++) {
			sum += (double)data[i];
		}
		value.average = sum / AMOUNT_OF_DATA;
		return value;
	}
	else {
		int i = 0;
		struct thread_info * inf = calloc(SEVERAL_THREADS, sizeof(struct thread_info));
		struct mean_variance common = {0, 0};
		inf[i].addend = AMOUNT_OF_DATA / SEVERAL_THREADS;
		for(i = 1; i < SEVERAL_THREADS; i++) {
			inf[i].addend = inf[0].addend;
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			inf[i].th_mark = i + 1;
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			inf[i].start = (data + i * inf[i].addend);
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			inf[i].values = calloc(1, sizeof(struct mean_variance));
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			int err = pthread_create(&inf[i].th_mark, NULL, &thread_work, &inf[i]);
			if(err != 0) perror("create");
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			pthread_join(inf[i].th_mark, NULL);
		}
		for(i = 0; i < SEVERAL_THREADS; i++) {
			common.average += inf[i].values->average;
		}
		common.average = common.average / SEVERAL_THREADS;
		for(i = 0; i < SEVERAL_THREADS; i++) {
			free(inf[i].values);
		}
		free(inf);
		return common;
	}
}

void *thread_work(void *arg) {
	int i = 0;
	struct thread_info *tinfo = (struct thread_info*)arg;
	for(;i < tinfo->addend; i++) {
		tinfo->values->average += tinfo->start[i];
	}
	tinfo->values->average = tinfo->values->average / tinfo->addend;
	return NULL;
}
	
