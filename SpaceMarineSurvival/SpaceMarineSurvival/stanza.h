#pragma once

#include "cultista.h"
#include"chmarine.h"
#include "posseduto.h"

#include <vector>
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <random>
#include<string>


class nemico;
struct E_shot {
	double aimx;
	double aimy;
	double nowx;
	double nowy;
	bool erase = false;
	int dir;
	int speed;
};
struct ostacolo {
	float x;
	float y;
};


class stanza
{
public:
	stanza();
	bool isMovePossible(int dir,float nextpos,float now);
	bool checkCollision(float x, float y,double hitbox);
	std::vector<ostacolo>& getOstacoli();
	void addEnemy();
	nemico generaNemico();
	void gestisci();
	std::vector<nemico> & getNemici();
	void setMarx(double x);	void setMary(double y);
	double getMarx(); double getMary();
	void addShot(E_shot e);
	E_shot& updateShots(int i);
	int getShotSize();
	void eraseShot(int i);
	bool checkEnemyCollision(float x, float y, double hitbox);
	bool checkMarineCollision(double x, double y, double hitbox);
private:

	int lunghezza, altezza;
	int contaround;
	int contanemici;
	int wave[3] = { 10,15,20 };
	float top,bot,right,left;
	ostacolo ostacolo1;
	ostacolo ostacolo2;
	std::vector<ostacolo> ostacoli;
	std::vector<nemico> nemici;
	std::vector<E_shot> colpi;
	double marx, mary;
};
