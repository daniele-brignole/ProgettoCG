#include "posseduto.h"



posseduto::posseduto(int id,stanza* s):nemico(s)
{
	pv = 10;
	this->id = id;
	mov = 0.01;
	setMov(mov);
	moving = false;
	rivolto = 1;
	setId(1);
}


posseduto::~posseduto()
{
}
