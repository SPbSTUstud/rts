#include "StdAfx.h"
#include "Barbershop.h"

Barbershop::Barbershop(void)
{
}

Barbershop::~Barbershop(void)
{
}

void Barbershop::HireBarber(Barber barber)
{
	printf("Barbershop hire barber\n");
	myBarber = barber;
}

void Barbershop::Open()
{
	printf("Barbershop opens\n");
	myBarber.StartWork(myWaitRoom);
}

void Barbershop::ComeIn(Visitor visitor)
{
	printf("Visitor come\n");
	myWaitRoom.Sit(&visitor);
	if (myBarber.IsSleep())
		myBarber.WakeUp();
}

void Barbershop::Close()
{
	myBarber.StopWork();
}
