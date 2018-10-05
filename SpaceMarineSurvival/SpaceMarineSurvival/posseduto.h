#pragma once
#include "nemico.h"
class posseduto :
	public nemico
{
public:
	posseduto(int id);
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

