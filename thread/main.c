#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define AMOUNT_OF_DATA 100000000
#undef RAND_MAX 
#define RAND_MAX 50
#define NO_THREADS 0

struct thread_info {
	pthread_t th_mark; 
	int *start;
	int addend; 					//The quantity of numbers to count in a thread.
	struct return_data *values;
};

struct return_data {
	double average;
	double dispersion;
	double time_spent;
};

struct return_data calculate(int number_of_threads, int *data);
void *thread_work(void * arg);
void create_data(int * array);

int main() {
	int number_of_threads = 0;
	int *data = calloc(AMOUNT_OF_DATA, sizeof(int));
	struct return_data val_no_thr = {0, 0};
	struct return_data val = {0, 0};
	printf("Enter a number of threads:\n");
	scanf("%d", &number_of_threads);
	create_data(data);
	val_no_thr = calculate(NO_THREADS, data);
	val = calculate(number_of_threads, data);
	printf("\nNo threads\nAverage value: %f\nDispersion: %f\nTime spent: %f\n", val_no_thr.average, val_no_thr.dispersion, val_no_thr.time_spent);
	printf("\n%d threads\nAverage value: %f\nDispersion: %f\nTime spent: %f\n", number_of_threads, val.average, val.dispersion, val.time_spent);
	free(data);
	return 0;
}

void create_data(int * array) {
	int i = 0;
	for(; i < AMOUNT_OF_DATA; i++) {
		array[i] = rand() % RAND_MAX - RAND_MAX / 2;
	}
}

struct return_data calculate(int number_of_threads, int *data) {
	if(!number_of_threads) {
		struct return_data value = {0, 0, 0};
		double sum_disp = 0;
		int i = 0;
		clock_t begin = clock();
		for( ; i < AMOUNT_OF_DATA; i++) {
			sum_disp += (double)data[i];
		}
		value.average = sum_disp / AMOUNT_OF_DATA;
		sum_disp = 0;
		for(i = 0; i < AMOUNT_OF_DATA; i++) {
			sum_disp += (data[i] - value.average) * (data[i] - value.average);
		}
		value.dispersion = sum_disp / AMOUNT_OF_DATA;
		clock_t end = clock();
		value.time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		return value;
	}
	else {
		int i = 0;
		struct thread_info * inf = calloc(number_of_threads, sizeof(struct thread_info));
		struct return_data common = {0, 0, 0};
		inf[i].addend = AMOUNT_OF_DATA / number_of_threads;
		for(i = 0; i < number_of_threads; i++) {
			inf[i].addend = inf[0].addend;
			inf[i].th_mark = i + 1;
			inf[i].start = (data + i * inf[i].addend);
			inf[i].values = calloc(1, sizeof(struct return_data));
		}
		clock_t begin = clock();
		for(i = 0; i < number_of_threads; i++) {
			int err = pthread_create(&inf[i].th_mark, NULL, &thread_work, &inf[i]);
			if(err != 0) perror("create");
		}
		for(i = 0; i < number_of_threads; i++) {
			pthread_join(inf[i].th_mark, NULL);
			common.average += inf[i].values->average;
			common.dispersion += inf[i].values->dispersion;
		}
		common.average = common.average / number_of_threads;
		common.dispersion = common.dispersion / number_of_threads;
		clock_t end = clock();
		common.time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		for(i = 0; i < number_of_threads; i++) {
			free(inf[i].values);
		}
		free(inf);
		return common;
	}
}

void *thread_work(void *arg) {
	int i = 0;
	struct thread_info *tinfo = (struct thread_info*)arg;
	for( ;i < tinfo->addend; i++) {
		tinfo->values->average += tinfo->start[i];
	}
	tinfo->values->average = tinfo->values->average / tinfo->addend;
	for(i = 0; i < tinfo->addend; i++) {
		tinfo->values->dispersion += (tinfo->start[i] - tinfo->values->average) * (tinfo->start[i] - tinfo->values->average);
	}
	tinfo->values->dispersion = tinfo->values->dispersion / tinfo->addend;
	return NULL;
}

