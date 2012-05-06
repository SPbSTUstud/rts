// haircutter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include "Barbershop.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));

	Barbershop barbershop = Barbershop();

	Barber barber = Barber();	
	barbershop.HireBarber(barber);
	barbershop.Open();

	int i = 0;
	while (i < 150)
	{
		Visitor v1 = Visitor();
		Sleep(rand() % 90);
		barbershop.ComeIn(v1);
		i++;
	}
	
	while (1)
	{
	}
	
	return 0;
}


