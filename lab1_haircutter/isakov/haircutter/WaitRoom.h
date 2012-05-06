#pragma once
#include "Visitor.h"

class WaitRoom
{
public:
	WaitRoom(void);
	~WaitRoom(void);
	void Sit(Visitor* visitor);
	Visitor* Call();
};