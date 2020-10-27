#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>

#define MAX_THREAD_CNT 10

int threadCount;

void* threadFunc(void* args);

void* threadOddEvenFunc(void* args);

int main(int argc, char** argv) {
	
	long thread;
	pthread_t threadHandles[MAX_THREAD_CNT];
	
	// Ustalenie liczby w¹tków
	if (argv[1]) {
		threadCount = strtol(argv[1], NULL, 10);
	} else {
		threadCount = MAX_THREAD_CNT;
	}
	
	// Tworzenie w¹tków
	//for (thread = 0; thread < threadCount; thread++){
	//	pthread_create(&threadHandles[thread], NULL, threadFunc, (void*)(thread));
	//}
	
	//Tworzenie w¹tków oddzienie dla parzystych i nieparzystych
	for (thread = 0; thread < threadCount; thread++){
		pthread_create(&threadHandles[thread], NULL, threadOddEvenFunc, (void*)(thread));
	}
	
	// Zakoñczenie pracy
	for (thread = 0; thread < threadCount; thread++){
		pthread_join(threadHandles[thread], NULL);
	}
	
	printf("Wszystkie w¹tki zakoñczy³y pracê");
	
	return 0;
}

// funkcja w¹tku
void* threadFunc(void* args) {
	
	//printf("Hello from thread %d\n", (int) args);
	std::cout << "Hello from thread " << (int) args << std::endl;
	return NULL;
	
}

void* threadOddEvenFunc(void* args) {
	
	if ((int) args % 2 == 1) {
		printf("Hello from odd thread %d\n", (int) args);
	} else {
		printf("Hello from even thread %d\n", (int) args);
	}

	return NULL;
	
}




