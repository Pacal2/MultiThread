#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>

#define MAX_THREAD_CNT 10

int threadCount;

void* threadFunc(void* args);

int main(int argc, char** argv) {
	
	long thread;
	pthread_t threadHandles[MAX_THREAD_CNT];
	
	// Ustalenie liczby w�tk�w
	if (argv[1]) {
		threadCount = strtol(argv[1], NULL, 10);
	} else {
		threadCount = MAX_THREAD_CNT;
	}
	
	// Tworzenie w�tk�w
	for (thread = 0; thread < threadCount; thread++){
		pthread_create(&threadHandles[thread], NULL, threadFunc, (void*)(thread));
	}
	
	// Zako�czenie pracy
	for (thread = 0; thread < threadCount; thread++){
		pthread_join(threadHandles[thread], NULL);
	}
	
	printf("Wszystkie w�tki zako�czy�y prac�");
	
	return 0;
}

// funkcja w�tku
void* threadFunc(void* args) {
	
	//printf("Hello from thread %d\n", (int) args);
	std::cout << "Hello from thread " << (int) args << std::endl;
	return NULL;
	
}




