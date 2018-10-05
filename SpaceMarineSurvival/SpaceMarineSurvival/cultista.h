#pragma once
#include "nemico.h"
class cultista: public nemico
{
public:
	cultista();
	cultista(int id);
	~cultista();
	void move();
	int getRivolto();
	bool isMoving();
	int getID();
	
private:
	int id;
	int pv;
	float mov;
	int rivolto;
	bool moving;
};

