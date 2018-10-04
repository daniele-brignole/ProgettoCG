#include "nemico.h"



nemico::nemico()
{
	rivolto = 1;
	moving = false;
}


nemico::~nemico()
{
}

int nemico::getRivolto()
{
	return rivolto;
}

bool nemico::isMoving()
{
	return moving;
}
