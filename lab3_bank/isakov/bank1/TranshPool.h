#pragma once

class TranshPool
{
private:
	bool* transhPool;
	int maxTransh;
public:
	TranshPool(void);
	TranshPool(int);
	~TranshPool(void);
	int OpenTransh();
	void CloseTransh(int);
};

