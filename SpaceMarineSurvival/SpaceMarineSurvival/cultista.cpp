#include "cultista.h"



cultista::cultista()
{
	
}

cultista::cultista(int id)
{
	this->id = id;
	pv = 3;
	rivolto = 1;
	moving = false;
	mov = 0.008;
}


cultista::~cultista()
{
}
