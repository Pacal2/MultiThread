#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int thread_count;
void *send_msg(void *rank);

#define MAX_THREAD_COUNT 20

char *messages[MAX_THREAD_COUNT];
// Dodanie semaforów:
sem_t semaphores[MAX_THREAD_COUNT];

int main(int argc, char** argv) {
	
	long thread;
	thread_count = strtol(argv[1], NULL, 10);
	
	pthread_t thread_handles[thread_count];
	
	// Inicjalizacja semaforów
	for (thread = 0; thread < thread_count; thread++) {
		sem_init(&semaphores[thread], 0, 0);
	}
	
	for (thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_handles[thread], NULL, send_msg, (void*) thread);
	}
	
	for (thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}
	// Zniszczenie semaforów
	for (thread = 0; thread < thread_count; thread++) {
		sem_destroy(&semaphores[thread]);
	}
	
	printf("THE END\n");
	
	return 0;
}

#define MSG_MAX 50
void *send_msg(void *rank){
	
	long my_rank = (long) rank;
	long dest = (my_rank + 1) % thread_count;
	long source = (my_rank + thread_count - 1) % thread_count;
	char *my_msg = (char *) malloc(MSG_MAX*sizeof(char));
	
	sprintf(my_msg, "Hello to %ld from %ld", dest, my_rank);
	messages[dest] = my_msg;
	// Implementacja semaforów w funkcji w¹tku
	sem_post(&semaphores[dest]);
	
	sem_wait(&semaphores[my_rank]);
	
	//if (messages[my_rank] != NULL) {
	//	printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	//} else {
		printf("Thread %ld > No message from %ld\n", my_rank, source);
	//}
	
	return NULL;

}



