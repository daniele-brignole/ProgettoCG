#pragma once
#include "nemico.h"
class cultista: public nemico
{
public:
	cultista();
	cultista(int id);
	~cultista();
	void move();
	
	int getID();
	
private:
	int id;
	int pv;
	float mov;
	
};

