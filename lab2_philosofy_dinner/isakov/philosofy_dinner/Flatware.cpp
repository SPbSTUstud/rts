#include "StdAfx.h"
#include "Flatware.h"

Flatware::Flatware(void)
{
	static int no = 0;
	captured = false;
	id = no++;
}


Flatware::~Flatware(void)
{
}


bool Flatware::Capture()
{	
	if (!captured)
	{
		//possible deadlock :(
		HANDLE hMutex = CreateMutex(NULL, TRUE, L"FlatwareData" + id);
		if (!captured)
		{
			captured = true;			
			ReleaseMutex(hMutex); 
			CloseHandle(hMutex);
			printf("Flatware %d captured\n", id);
			return true;
		}
		ReleaseMutex(hMutex); 
		CloseHandle(hMutex);
	}
	return false;
}

bool Flatware::Release()
{
	if (captured)
	{
		//possible deadlock :(
		//todo: use mutex
		if (captured)
		{
			captured = false;
			printf("Flatware %d released\n", id);
			return true;
		}
	}
	//exception !!!
	return false;
}
