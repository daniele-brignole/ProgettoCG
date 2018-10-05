#pragma once
#include "nemico.h"
class chmarine :
	public nemico
{
public:
	chmarine(int id);
	~chmarine();
	int getRivolto();
	bool isMoving();
private:
	int id;
	int pv;
	float mov;
	int rivolto;
	bool moving;
};

