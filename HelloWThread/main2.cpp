#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>

#define MAX_THREAD_CNT 10

int threadCount;

typedef struct {
	int numer;
	std::string miasto;
}
tContext;

void* threadFunc(void* args);


int main(int argc, char** argv) {
	
	long thread;
	pthread_t threadHandles[MAX_THREAD_CNT];
	std::string miasta[MAX_THREAD_CNT] = {"Berlin", "Moskwa", "Pary�", "Hanower", "Warszawa", "Helsinki", "Ateny", "Ansterdam", "Lizbona", "Genewa"};
	// Tablica kontekst�w wywo�ania dla poszczeg�lnych w�tk�w
	tContext ctxData[MAX_THREAD_CNT];
	
	// Ustalenie liczby w�tk�w
	if (argv[1]) {
		threadCount = strtol(argv[1], NULL, 10);
	} else {
		threadCount = MAX_THREAD_CNT;
	}
	
	//Tworzenie w�tk�w
	for (thread = 0; thread < threadCount; thread++){
		ctxData[thread].numer = thread;
		ctxData[thread].miasto = miasta[thread];
		pthread_create(&threadHandles[thread], NULL, threadFunc, (void*)(ctxData + thread));
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
	
	tContext* ctx = (tContext*)args;
	printf("Hello from thread %d! Govorit %s\n", ctx->numer, ctx->miasto.c_str());
	return NULL;
	
}

	

