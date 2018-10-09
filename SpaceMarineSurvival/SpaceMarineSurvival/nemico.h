#pragma once


//#include "stanza.h"
#include <stdio.h>
#include<iostream>
#include <random>

class stanza;
class nemico
{
public:
	nemico(stanza* context);
	~nemico();
	void decidi();
	void setId(int id);
	int getId();
	int conta;
	int direction;
	float getPosx();
	float getPosy();
	void move();
	void spara();
	void moveClose();
	void setMov(float mov);
private:
	int id;
	float posx, posy;
	float mov;
	stanza* stz;
	int wait = 10;
};

