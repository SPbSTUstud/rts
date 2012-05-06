#pragma once
#include "bank.h"

class Client
{
private:
	int maxNeed;
	int wantNow;
	int getAlready;
	int transhID;
	Bank* bank;
	HANDLE threadHandle;
	void StartThread();
public:
	Client(Bank*, int);
	~Client(void);
	int GetMoneyLeft();
	bool TakeCredit(int);
	bool ReturnMoney();
};

