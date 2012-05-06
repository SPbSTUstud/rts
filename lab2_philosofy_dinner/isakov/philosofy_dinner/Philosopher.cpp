#include "StdAfx.h"
#include "Philosopher.h"

using namespace std;

DWORD WINAPI Speak(LPVOID);

//Thread Routine
DWORD WINAPI Speak(LPVOID lpdwThreadParam )
{
	srand(time(0));	
	Philosopher* philosopher = (Philosopher*)lpdwThreadParam;

	while(1)
	{
		printf("Philosopher %d speak about everything and nothing\n", philosopher->id);
		//todo: some times hungry
		int a = 5000000000 + rand() % 100000;
		while(a)
			a--;
		printf("Philosopher %d hungry\n", philosopher->id);
		philosopher->Eat();
	}	
	return 0;
}

Philosopher::Philosopher(void)
{
	static int no = 0;
	id = no++;
}

Philosopher::~Philosopher(void)
{
}

void Philosopher::Sit(Flatware* left, Flatware* right)
{
	printf("Philosopher %d remember his flatwares\n", id);
	lefthand = left;
	righthand = right;
	printf("Philosopher %d have good memory :)\n", id);
}

void Philosopher::StartPhilosophize()
{
	DWORD dwThreadId;

	threadHandle = CreateThread(NULL, //Choose default security
		0, //Default stack size
		(LPTHREAD_START_ROUTINE)&Speak,
		//Routine to execute
		(LPVOID)this, //Thread parameter
		0, //Immediately run the thread
		&dwThreadId //Thread Id
		);

	if (threadHandle == NULL)
	{
		printf("Philosopher %d sick, can't speak today\n", id);		
	}
	else
	{
		printf("Philosopher %d start speak\n", id);
	}	
}

void Philosopher::Eat()
{
	printf("Philosopher %d looking for left flatware\n", id);
	int n = 10;
	bool result = false;
	while(n && !result)
	{
		n--;
		result = lefthand->Capture();
	}
	if (!result)
	{
		printf("Philosopher %d can't take left flatware\n", id);
		return;
	}

	printf("Philosopher %d looking for right flatware\n", id);
	n = 10;
	result = false;
	while(n && !result)
	{
		n--;
		result = righthand->Capture();
	}
	if (!result)
	{
		printf("Philosopher %d can't take right flatware\n", id);
		return;
	}
	//eat awhile
	printf("Philosopher %d eat\n", id);
	n = 10000;
	while(n)
		n--;
		
	printf("Philosopher %d finish eating\n", id);
	lefthand->Release();
	righthand->Release();	
}