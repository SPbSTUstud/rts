#pragma once
#include "Philosopher.h"
#include "Flatware.h"

class Table
{
private:
	Philosopher* philosophers;
	Flatware* flatwares;
public:
	Table(int);
	~Table(void);
};

