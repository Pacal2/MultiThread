#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
void *Thread_sum(void *rank);

int n;
double sum;
volatile int flag;

int main(int argc, char** argv) {
	
	long thread;
	thread_count = strtol(argv[1], NULL, 10);
	sum = 0.0;
	n = 1000;
	
	pthread_t thread_handles[thread_count];
	
	for (thread = 0; thread < thread_count; thread ++) {
		pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);
	}
	
	for (thread = 0; thread < thread_count; thread ++) {
		pthread_join(thread_handles[thread], NULL);
	}
	
	printf("Pi Estimate in %d iterations %d threads is: %.10f\n", n, thread_count, 4*sum);
	
	return 0;
	
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void *Thread_sum(void *rank) {
	
	long my_rank = (long) rank;
	double factor, loc_sum;
	long long i;
	long long loc_n = n/thread_count;
	long long first = loc_n * my_rank;
	long long last = first + loc_n;
	
	//factor = (first % 2 == 0 ? 1.0 : -1.0);
	if (first % 2 == 0) {
		factor = 1.0;
	} else {
		factor = 1.0;
	}
	
	
	for(i=first; i<last; i++, factor = -factor) {
		
		while (flag != my_rank);
		sum += factor/(2 * i + 1);
		flag = (flag + 1) % thread_count;
	}
	
	return NULL;
	
}
#pragma GCC pop_options

