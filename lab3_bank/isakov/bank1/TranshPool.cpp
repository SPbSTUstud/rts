#include "stdafx.h"
#include "TranshPool.h"

TranshPool::TranshPool(void)
{
	printf("dummy thing created\n");
}

TranshPool::TranshPool(int poolSize)
{
	maxTransh = poolSize;
	transhPool = new bool[maxTransh];
	for(int i = 0; i<maxTransh; i++)
		transhPool[i] = false;
}


TranshPool::~TranshPool(void)
{
	//if (transhPool != nullptr)
	//	delete(transhPool);
}

int TranshPool::OpenTransh()
{
	//mutex?
	printf("Trying open transh\n");
	for(int i=0; i<maxTransh; i++)
		if (!transhPool[i])
		{
			printf("transh %d opened\n", i);
			transhPool[i] = true;
			return i;
		}
	printf("transh don't open\n");
	return -1;
}

void TranshPool::CloseTransh(int id)
{
	//mutex?
	transhPool[id] = false;
	printf("transh %d was closed\n", id);
}
