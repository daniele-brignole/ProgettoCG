#include "nemico.h"
#include "stanza.h"


nemico::nemico(stanza* stz,int pv)
{
	conta = 0;
	this->stz = stz;
	this->pv = pv;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_real_distribution<> distrx(-1.30, 1.30);
	posx = (float) distrx(eng);
		
	std::uniform_real_distribution<> distry(-1, 1);
	posy = (float) distry(eng);
		
}


nemico::~nemico()
{
}

void nemico::decidi()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,100);
	int decisionNumber = distr(eng);
	now = clock();
	if (remain < 0 || last > 0) {
		remain = (double)(now - last) / (double)CLOCKS_PER_SEC;
	}
	if (decisionNumber < 60) move();
	else {
		if (remain >= 1.5) {
			last = clock();
			spara();
			remain = -1;
		}
	}
	
}

void nemico::setId(int id)
{
	this->id = id;
}

int nemico::getId()
{
	return id;
}

int nemico::getVerso()
{
	return verso;
}

float nemico::getPosx()
{
	return posx;;
}

float nemico::getPosy()
{
	return posy;
}

void nemico::move()
{
	conta--;
	if (conta <= 0) {
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, 3);
		direction = distr(eng);
		conta = 30;
	}

	
		switch (direction) {
		case 0:
			if (stz->isMovePossible(direction, posy + mov, posx)) {
				posy = posy + mov;
			}
			break;
		case 1:
			if (stz->isMovePossible(direction, posx + mov, posy)) {
				posx = posx + mov;
				
			}
			break;
		case 2:
			if (stz->isMovePossible(direction, posy - mov, posy)) {
				posy = posy - mov;
				
			}
			break;
		case 3:
			if (stz->isMovePossible(direction, posx - mov, posy)) {
				posx= posx - mov;
				
			}
			break;
		}
}

void nemico::spara()
{
	//definizione sparo
	E_shot shot;
	shot.aimx = stz->getMarx();
	shot.aimy = stz->getMary();
	shot.nowx = posx;
	shot.nowy = posy;
	//determinazione verso
	if (this->id == 0) {
		shot.type = 18;
		if (shot.aimx >= shot.nowx) verso = 11;
		else verso = 10;
	}
	else if (this->id == 2) {
		shot.type = 19;
		double coeffangol = (shot.nowy - shot.aimy) / (shot.nowx - shot.aimx);
		if (shot.aimx < shot.nowx) {
			if (coeffangol > 1) verso = 14;
			else if (coeffangol < -1) verso = 12;
			else verso = 15;
		}
		else{
			if (coeffangol > 1) verso = 12;
			else if (coeffangol < -1) verso = 14;
			else verso = 13;
		}
	}
	
	
	
	//determinazione asse incrementante
	if (abs(shot.nowx - shot.aimx) >= abs(shot.nowy - shot.aimy)) shot.speed = 0;
	else shot.speed = 1;
	if (shot.speed == 0) {
		if (shot.aimx <= shot.nowx) shot.dir = 0;
		else shot.dir = 1;
	}
	else{
		if (shot.aimy <= shot.nowy) shot.dir = 1;
		else shot.dir = 0;
	}
	stz->addShot(shot);
	
}

void nemico::moveClose()
{
	this->verso = 16;
	double tarx = stz->getMarx();
	double tary = stz->getMary();
	int increment;
	if (!(posx +0.05 >= tarx-0.05 && posy + 0.05 >= tary-0.05 && 
		posx - 0.05 <= tarx + 0.05 && posy - 0.05 <= tary + 0.05)) {
		double temp;
		if (abs(posx - tarx) >= abs(posy - tary)) increment = 0; // 0 -> incremento su x
		else increment = 1;										// 1 -> incremento su y
		
		if (increment == 0) {
			if (tarx <= posx) temp = posx - mov;
			else temp = posx + mov;
			this->posy = (temp - tarx)*(posy - tary) / (posx - tarx) + tary;
			this->posx = temp;
		}
		else {
			if (tary <= posy) temp = posy - mov;
			else temp = posy + mov;
			this->posx = (temp - tary)*(posx - tarx) / (posy - tary) + tarx;
			this->posy = temp;
		}		
	}
	else this->attack = true;
}
void nemico::setMov(float mov) {
	this->mov = mov;
}

bool nemico::damage()
{
	this->pv = this->pv - 2;
	if (this->pv <= 0) return true;
	else return false;
}

bool nemico::getAttack()
{
	return attack;
}

bool nemico::isMorto()
{
	return this->morto;
}

void nemico::setMorto(bool m)
{
	this->morto = m;
}


