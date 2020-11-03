// JoinThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;
int numberOfThreads;

unsigned __stdcall threadFunc(void * args) {
	unsigned int rank = (int)(args);
	Sleep(500*(rank+1));
	cout << "Hello from thread" << rank << "/" << numberOfThreads << endl;
	return rank;
}

int main()
{
	HANDLE *threads;
	cout << "Podaj liczbe watkow: " << endl;
	cin >> numberOfThreads;

	threads = new HANDLE[numberOfThreads];

	for (int i = 0; i < numberOfThreads; i++) {
		threads[i] = (HANDLE)_beginthreadex(NULL, 0, threadFunc, (void *)i, 0, NULL);
	}

	cout << "Thread running" << endl;

	DWORD res = WaitForMultipleObjects(numberOfThreads, threads, true, INFINITE);

	cout << "All the threads finished their job" << endl;

	for (int i = 0; i < numberOfThreads; i++) {
		CloseHandle(threads[i]);
	}
	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
