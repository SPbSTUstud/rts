#pragma once
#include "Barber.h"

class Barbershop
{
private:
	Barber myBarber;
	WaitRoom myWaitRoom;	
public:
	Barbershop(void);
	~Barbershop(void);
	void HireBarber(Barber barber);
	void ComeIn(Visitor visitor);
	void Open();
	void Close();
};