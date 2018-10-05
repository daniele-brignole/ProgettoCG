#include "chmarine.h"



chmarine::chmarine(int id)
{
	pv = 6;
	this->id = id;
	mov = 0.001;
	moving = false;
	rivolto = 1;
	setId(0);
}


chmarine::~chmarine()
{
}
