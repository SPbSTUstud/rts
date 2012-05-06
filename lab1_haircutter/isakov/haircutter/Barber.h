#pragma once
#include "WaitRoom.h"

class Barber
{
private:
	int threadID;
	WaitRoom myRoom;
public:
	Barber(void);
	~Barber(void);
	void Haircut(Visitor* visitor);
	void StartWork(WaitRoom room);
	void StopWork();
	bool IsSleep();
	void WakeUp();
};
