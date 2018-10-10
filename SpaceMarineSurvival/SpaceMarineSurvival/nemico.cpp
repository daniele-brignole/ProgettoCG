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
	E_shot shot;
	shot.aimx = stz->getMarx();
	shot.aimy = stz->getMary();
	shot.nowx = posx;
	shot.nowy = posy;
	if (shot.aimx <= shot.nowx) shot.dir = 0;
	else shot.dir = 1;
	stz->addShot(shot);
}

void nemico::moveClose()
{

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


