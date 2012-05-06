// bank1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, L"BankMutex");
	ReleaseMutex(hMutex);

	Bank bank = Bank(2000000);
	Client c1 = Client(&bank, 2000);
	Client c2 = Client(&bank, 2000000);
		
	while(1) {};

	CloseHandle(hMutex);
	return 0;
}

