#include "StdAfx.h"
#include "Table.h"

Table::Table(int n)
{
	philosophers = new Philosopher[n];
	flatwares = new Flatware[n];
	philosophers[0].Sit(&flatwares[n-1], &flatwares[0]);
	for(int i=1; i<n; i++)
	{
		philosophers[i].Sit(&flatwares[i-1], &flatwares[i]);
	}
	for (int i=0; i<n; i++)
	{
		philosophers[i].StartPhilosophize();
	}
}


Table::~Table(void)
{
}
