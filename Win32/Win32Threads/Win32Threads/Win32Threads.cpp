// Win32Threads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;

unsigned __stdcall threadFunc(void * args) {
	unsigned int n = (int)(args);
	Sleep(200);
	return n;
}

int main()
{
	HANDLE th;
	//unsigned ID;
	int retval;
	cout << "Podaj zwracana wartosc: " << endl;
	cin >> retval;

	//th = (HANDLE)_beginthreadex(NULL, 0, threadFunc, (void *)retval, 0, &ID);
	th = (HANDLE)_beginthreadex(NULL, 0, threadFunc, (void *)retval, 0, NULL);

	if (th == 0) {
		cout << "_beginthreadex failed" << endl;
		return -1;
	}
	cout << "Thread running" << endl;
	DWORD res = WaitForSingleObject(th, INFINITE);
	cout << "Wait for thread result: " << res << endl;
	DWORD dwExit;
	GetExitCodeThread(th, &dwExit);
	cout << "Thread exit code was: " << dwExit << endl;
	/*
	for (;;) {
		DWORD dwExit;
		GetExitCodeThread(th, &dwExit);
		if (dwExit == STILL_ACTIVE) {
			cout << endl << "Thread still running ..." << endl;
		}
		else {
			cout << endl << "Thread exit code was: " << dwExit << endl;
			break;
		}
	}
	*/
	CloseHandle(th);
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
