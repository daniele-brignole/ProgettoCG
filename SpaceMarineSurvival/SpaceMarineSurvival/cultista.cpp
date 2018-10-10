#include "cultista.h"





cultista::cultista(int id,stanza* s):nemico(s,3)
{
	this->id = id;
	pv = 3;
	mov = 0.008;
	setMov(mov);
	moving = false;
	rivolto = 1;
	setId(0);
}


cultista::~cultista()
{
}
