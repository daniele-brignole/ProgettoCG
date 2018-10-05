#include "cultista.h"



cultista::cultista()
{
	
}

cultista::cultista(int id)
{
	this->id = id;
	pv = 3;
	mov = 0.008;
	moving = false;
	rivolto = 1;
	setId(0);
}


cultista::~cultista()
{
}
