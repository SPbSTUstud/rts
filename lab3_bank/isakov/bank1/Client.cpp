#include "stdafx.h"
#include "Client.h"

DWORD WINAPI Routine(LPVOID);

//Thread Routine
DWORD WINAPI Routine(LPVOID lpdwThreadParam )
{
	srand(time(0));	
	Client* client = (Client*)lpdwThreadParam;

	bool returnMoney = false;
	while(!returnMoney)
	{
		//todo: some times take money
		int a = 500000 + rand() % 100000;
		while(a)
			a--;
		int wantNow = rand() % (client->GetMoneyLeft());
		if (wantNow == 0)
			wantNow++;

		if (client->TakeCredit(wantNow) && client->GetMoneyLeft() == 0)
			returnMoney = true;
	}	
	client->ReturnMoney();
	return 0;
}

void Client::StartThread()
{
	DWORD dwThreadId;

	threadHandle = CreateThread(NULL, //Choose default security
		0, //Default stack size
		(LPTHREAD_START_ROUTINE)&Routine,
		//Routine to execute
		(LPVOID)this, //Thread parameter
		0, //Immediately run the thread
		&dwThreadId //Thread Id
		);

	if (threadHandle == NULL)
	{
		printf("Error can't start thread\n");		
	}
	else
	{
		printf("start thread\n");
	}	
}

Client::Client(Bank* myBank, int maxNeed)
{
	this->maxNeed = maxNeed;
	this->bank = myBank;
	getAlready = 0;
	wantNow = 0;
	transhID = -1;
	StartThread();
	printf("Client was born\n");
}

Client::~Client(void)
{
	printf("Client die\n");
}

int Client::GetMoneyLeft()
{
	return maxNeed - getAlready;
}

bool Client::TakeCredit(int now)
{
	printf("Client go to bank (transh %d)\n", transhID);
	bool result = bank->TakeCredit(&transhID, now, maxNeed - getAlready);
	printf("Bank give money? %d\n", result);
	if (result)
		getAlready += now;
	return result;
}

bool Client::ReturnMoney()
{
	printf("Client return money to bank (transh %d)\n", transhID);
	bool result = bank->ReturnCredit(&transhID, maxNeed);
	return result;
}
