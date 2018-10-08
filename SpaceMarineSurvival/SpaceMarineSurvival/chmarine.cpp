#include "chmarine.h"



chmarine::chmarine(int id,stanza* s) :nemico(s)
{
	pv = 6;
	this->id = id;
	mov = 0.001;
	setMov(mov);
	moving = false;
	rivolto = 1;
	setId(0);
}


chmarine::~chmarine()
{
}
