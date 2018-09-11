#include "Marine.h"





Marine::~Marine()
{
}

void Marine::setPosition(float x, float y) {
	this->posx = x;
	this->posy = y;
}

void Marine::setLoS(float x, float y)
{
	this->losx = x;
	this->losy = y;
}
float Marine::getLosx() {
	return this->losx;
}

float Marine::getLosy()
{
	return losy;
}
