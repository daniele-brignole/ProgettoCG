#include "nemico.h"



nemico::nemico()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_real_distribution<> distrx(-1.30, 1.30);
	posx = (float) distrx(eng);
		//static_cast<double>(std::rand()) / RAND_MAX *1.30  - 1.30;
	std::uniform_real_distribution<> distry(-1, 1);
	posy = (float) distry(eng);
		//static_cast<double>(std::rand()) / RAND_MAX - 1;
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

