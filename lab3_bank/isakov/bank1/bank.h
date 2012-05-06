#pragma once
#include "TranshPool.h"

class Bank
{
private:
	int reserve;
	TranshPool pool;
	bool CheckClient(int,int);
public:
	Bank(int);
	~Bank(void);
	bool TakeCredit(int*, int, int);
	bool ReturnCredit(int*, int);
};

