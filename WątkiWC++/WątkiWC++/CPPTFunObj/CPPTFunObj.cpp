// CPPTFunObj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Worker {
private:
	unsigned int nIter;

public:
	Worker(unsigned maxIter) : nIter(maxIter) {}

	// Deklaracja atrybutu result (wynik)
	double result;

	void operator()(double val, double initial) {
		cout << "Worker: computing sqrt(" << val << "), iter = " << nIter << endl;
		double x, x1 = initial;
		for (int i = 0; i < nIter; i++) {
			x = x1 - (x1*x1 - val) / (2 * x1);
			if (fabs(x - x1) < 1e-6) {
				break;
			}
			x1 = x;
			cout << "Worker: iter " << i << ", estim = " << x1 << endl;
		}
		cout << "Worker: final answer -> sqrt(" << val << ") = " << x1 << endl;
		// Nadanie atrybutowi wartości
		result = x1;
	}


};

int main()
{
	Worker w(10000);
	auto startTime = chrono::high_resolution_clock::now();
	thread t(w, 2557, 4);
	// przekazadnie do konstruktora wątku referencji
	// thread t(std::ref(w), 2557, 4);
	cout << "Main: waiting for thread T" << endl;
	t.join();
	auto endTime = chrono::high_resolution_clock::now();
	cout << "main: done (" << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << " microseconds elapsed)" << endl;
	// Wyświetlenie wyniku
	cout << "result = " << w.result << endl;
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
