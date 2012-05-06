#include "StdAfx.h"
#include "Barber.h"

DWORD WINAPI ThreadProc(LPVOID);
HANDLE threadHandle;
HANDLE eventHandle;

Barber* myBarber;
bool isSleep;

//Thread Routine
DWORD WINAPI ThreadProc(LPVOID lpdwThreadParam )
{
	WaitRoom* myRoom = (WaitRoom*)lpdwThreadParam;	

	while(1)
	{
		printf("Barber go to wait room\n");
				
		Visitor* v = myRoom->Call();
		if (v == NULL)
		{
			isSleep = true;
			printf("Nobody in wait room. Barber go to sleep\n");			

			DWORD dwWaitResult;

			dwWaitResult = WaitForSingleObject( 
				eventHandle, // event handle
				INFINITE);    // indefinite wait

			isSleep = false;
			printf("Barber wake up. Barber start works\n");

			switch (dwWaitResult) 
			{
				// Event object was signaled
				case WAIT_OBJECT_0: 
					//
					// TODO: Read from the shared buffer
					//
					break; 

				// An error occurred
				default: 
					printf("Barber wake up from nightmare (%d)\n", GetLastError()); 
					return 0; 
			}
		}
		else
		{
			myBarber->Haircut(v);
		}
	}
	printf("Barber end work. Go home\n");
	return 0;
}

Barber::Barber(void)
{
}


Barber::~Barber(void)
{
}

void Barber::StartWork(WaitRoom room)
{	
	DWORD dwThreadId;

	eventHandle = CreateEvent(
	  NULL, //SECURITY_ATTRIBUTES
	  false, //BOOL bManualReset,
	  false, //BOOL bInitialState,
	  (LPCTSTR)"barberEvent" //LPCTSTR lpName
	);

	myBarber = this;

	threadHandle = CreateThread(NULL, //Choose default security
		0, //Default stack size
		(LPTHREAD_START_ROUTINE)&ThreadProc,
		//Routine to execute
		(LPVOID) &room, //Thread parameter
		0, //Immediately run the thread
		&dwThreadId //Thread Id
		);
	if (threadHandle == NULL)
	{
		printf("Barber not come at work. Maybe he's sick\n");		
	}
	else
	{
		printf("Barber start work\n");
	}		
}

void Barber::Haircut(Visitor* visitor)
{
	printf("Barber cut client\n");
	Sleep(100);
	printf("Barber finish cutting\n");		
}

void Barber::StopWork()
{
	printf("Barber stop work\n");
}

bool Barber::IsSleep()
{
	return isSleep;
}

void Barber::WakeUp()
{
	SetEvent(eventHandle);
	printf("Visitor wake ups barber\n");
}