#pragma once

class Flatware
{
private:
	bool captured;
	int id;
public:
	Flatware(void);
	~Flatware(void);
	bool Capture();
	bool Release();
};

