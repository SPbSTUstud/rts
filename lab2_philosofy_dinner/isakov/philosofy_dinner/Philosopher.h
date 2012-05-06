#pragma once
#include "Flatware.h"

class Philosopher
{
private:	
	HANDLE threadHandle;
	Flatware* lefthand;
	Flatware* righthand;	
public:	
	int id;
	Philosopher(void);
	~Philosopher(void);
	void Sit(Flatware*, Flatware*);
	void StartPhilosophize();
	void Eat();
};

