#include "posseduto.h"



posseduto::posseduto(int id,stanza* s):nemico(s,10)
{
	pv = 10;
	this->id = id;
	mov = 0.005;
	setMov(mov);
	moving = false;
	rivolto = 1;
	setId(1);
}


posseduto::~posseduto()
{
}
