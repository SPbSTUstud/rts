#include "StdAfx.h"
#include "Barbershop.h"

//room size;
const int N = 5;
int lastFreeSit;
Visitor* myVisitors;
//HANDLE myMutex;

WaitRoom::WaitRoom(void)
{	
	myVisitors = new Visitor[N];
	lastFreeSit = 0;
}

WaitRoom::~WaitRoom(void)
{
}

void WaitRoom::Sit(Visitor* visitor)
{
	HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCTSTR)"MyMutex");
	WaitForSingleObject(myMutex, INFINITE);
	//possible here need to add lock statement
	if (lastFreeSit < N)
	{
		printf("Visitor sit %d in wait room\n", lastFreeSit);
		myVisitors[lastFreeSit++];
	}
	else
	{
		printf("Visitor can't seat. No more chairs\n");
	}
	ReleaseMutex(myMutex);
	CloseHandle(myMutex);
}

Visitor* WaitRoom::Call()
{
	HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCTSTR)"MyMutex");
	WaitForSingleObject(myMutex, INFINITE);

	Visitor* res = NULL;	
	if (lastFreeSit != 0)
	{
		res = &myVisitors[0];
		for(int i=1; i<lastFreeSit; i++)
			myVisitors[i-1] = myVisitors[i];
		lastFreeSit--;
	}	
	ReleaseMutex(myMutex);
	CloseHandle(myMutex);
	return res;
}
