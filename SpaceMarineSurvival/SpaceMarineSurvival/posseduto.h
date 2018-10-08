#pragma once


#include "nemico.h"


class posseduto :
	public nemico
{
public:
	posseduto(int id,stanza* s);
	~posseduto();
	int getRivolto();
	bool isMoving();
private:
	int pv;
	int id;
	float mov;
	int rivolto;
	bool moving;
};

