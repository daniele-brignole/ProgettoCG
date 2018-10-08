#pragma once
#ifndef CHMAR_H
#define CHMAR_H
 // !CHMAR_H

#include "nemico.h"


class chmarine :
	public nemico
{
public:
	chmarine(int id,stanza* s);
	~chmarine();
	int getRivolto();
	bool isMoving();
private:
	int id;
	int pv;
	float mov;
	int rivolto;
	bool moving;
};

#endif