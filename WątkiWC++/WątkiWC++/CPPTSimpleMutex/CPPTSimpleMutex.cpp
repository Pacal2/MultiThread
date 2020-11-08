// CPPTSimpleMutex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

class Worker {
private:
	int rank;
public:
	Worker(int aRank) : rank(aRank) {}
	void operator()(int alter) {
		for (int i = 0; i < alter; i++) {
			mtx.lock();
			cout << "WRK" << rank << ":: performing iteration " << i << "/" << alter << endl;
			mtx.unlock;
		}
	}
};

int main()
{
	int nThreads;

	cout << "Podaj liczbę wątków: ";
	cin >> nThreads;

	thread** threads = new thread*[nThreads];

	for (int i = 0; i < nThreads; i++) {
		threads[i] = new thread(*(new Worker(i)), 10);
	}

	for (int i = 0; i < nThreads; i++) {
		threads[i]->join();
		delete threads[i];
	}

	delete threads;
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
