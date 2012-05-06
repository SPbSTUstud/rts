#include "stdafx.h"
#include "bank.h"

const int TRANSH_POOL_SIZE = 4;

Bank::Bank(int resourse)
{
	reserve = resourse;
	pool = TranshPool(TRANSH_POOL_SIZE);
}


Bank::~Bank(void)
{
	
}

bool Bank::CheckClient(int wantNow, int wantAll)
{
	int reserveAfterClient = reserve - wantNow;
	int wantLater = wantAll - wantNow;
	if (wantLater <= reserveAfterClient)
		return true;
	return false;
}

bool Bank::TakeCredit(int* transhID, int wantNow, int wantAll)
{
	HANDLE hMutex = OpenMutex(NULL, TRUE, L"BankMutex");

	WaitForSingleObject(
            hMutex,    // handle to mutex
            INFINITE);  // no time-out interval

    			if (*transhID == -1)
				{
					printf("new client (transh %d)\n", *transhID);
					bool trust = CheckClient(wantNow, wantAll);
					if (trust)
					{
						printf("we trust client (transh %d)\n", *transhID);
						int id = pool.OpenTransh();
						if (id != -1)
						{
							//need return transh id to client
							*transhID = id;
							printf("transh %d was open (transh %d)\n", id, *transhID);
						}
						return true;
					}
					printf("don't trust client (transh %d)\n", *transhID);
					return false;
				}
				else
				{
					printf("old client\n");
					bool trust = CheckClient(wantNow, wantAll);
					if (trust)
					{
						printf("trust to old client\n");
						return true;
					}
					printf("don't trust to old client\n");
					return false;
				}
 
					ReleaseMutex(hMutex); 
					CloseHandle(hMutex);
}

bool Bank::ReturnCredit(int* transhID, int sum)
{
	HANDLE hMutex = OpenMutex(NULL, TRUE, L"BankMutex");

	DWORD dwWaitResult = WaitForSingleObject(
            hMutex,    // handle to mutex
            INFINITE);  // no time-out interval

    switch (dwWaitResult) 
    {
        // The thread got ownership of the mutex
        case WAIT_OBJECT_0: 
            __try {				
				if (*transhID != -1)
				{
					pool.CloseTransh(*transhID);
					reserve += sum;
					return true;
				}
				return false;
			} 

            __finally { 
					ReleaseMutex(hMutex); 
					CloseHandle(hMutex);
			} 
            break; 

        // The thread got ownership of an abandoned mutex
        // The database is in an indeterminate state
        case WAIT_ABANDONED: 
            return false; 
    }
}
