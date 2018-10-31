#pragma once


//#include "stanza.h"
#include <stdio.h>
#include<iostream>
#include <random>
#include <time.h>
#include "audiere.h"
class stanza;
class nemico
{
public:
	nemico(stanza* context, int pv);
	~nemico();
	void decidi();
	void setId(int id);
	int getId();
	int conta;
	int getVerso();
	int direction;
	float getPosx();
	float getPosy();
	void move();
	void spara();
	void moveClose();
	void setMov(float mov);
	bool damage();
	bool getAttack();
	bool isMorto();
	void setMorto(bool m);
	void musicDeath();
private:
	int id;
	audiere::AudioDevicePtr device;
	audiere::OutputStreamPtr laser;
	//audiere::OutputStreamPtr death;
	bool morto = false;
	bool attack = false;
	int verso = 10;
	float posx, posy;
	float mov;
	stanza* stz;
	int wait = 10;
	clock_t now = 0;
	clock_t last = 0;
	double remain = 10.0;
	int pv;
};

