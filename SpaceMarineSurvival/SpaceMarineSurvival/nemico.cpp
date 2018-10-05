#include "nemico.h"



nemico::nemico()
{
	posx = static_cast<double>(std::rand()) / RAND_MAX *1.30  - 1.30;
	posy = static_cast<double>(std::rand()) / RAND_MAX - 1;
}


nemico::~nemico()
{
}

void nemico::decidi()
{
}

void nemico::setId(int id)
{
	this->id = id;
}

int nemico::getId()
{
	return id;
}

float nemico::getPosx()
{
	return posx;;
}

float nemico::getPosy()
{
	return posy;
}

void nemico::move()
{
}

