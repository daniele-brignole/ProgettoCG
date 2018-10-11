#include "chmarine.h"



chmarine::chmarine(int id,stanza* s) :nemico(s,6)
{
	pv = 6;
	this->id = id;
	mov = 0.003;
	setMov(mov);
	moving = false;
	rivolto = 1;
	setId(2);
}


chmarine::~chmarine()
{
}
