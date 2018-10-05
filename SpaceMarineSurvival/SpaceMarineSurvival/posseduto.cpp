#include "posseduto.h"



posseduto::posseduto(int id)
{
	pv = 10;
	this->id = id;
	mov = 0.01;
	moving = false;
	rivolto = 1;
	setId(1);
}


posseduto::~posseduto()
{
}
