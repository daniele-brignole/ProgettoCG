#include "Marine.h"
#include <math.h>




Marine::~Marine()
{
}

void Marine::setPosition(float x, float y) {
	this->posx = x;
	this->posy = y;
}

void Marine::setLoS(float x, float y)
{
	this->losx = x;
	this->losy = y;
}
float Marine::getLosx() {
	return this->losx;
}

float Marine::getLosy()
{
	return losy;
}

int Marine::calcolaVisuale()
{
	/*double coeffangol;
	coeffangol = (losy - posy) / (losx - posx);
	double angolo = atan(coeffangol)*180/3.14;
	//double prova = atan2(1.0,1.0);
	if (losy >= posy) {
		if (angolo < 45.0) return 2;
		else if (angolo >= 45.0 && angolo <= 135.0) return 1;
		else if (angolo > 135.0) return 4;
	}
	if (losy < posy) {
		if (angolo > 45.0) return 2;
		else if (angolo <= 45.0 && angolo <= 135.0) return 3;
		else if (angolo < 135.0) return 4;
	}
	*/
	float lx, ly;
	lx = losx + posx;
	ly = losy + posy;
	if (lx > posx) {
		if (ly > lx && ly > posy) return 1;
		else if (ly < lx && ly < posy) return 3;
		else if (ly < lx && ly > - lx) return 2;
	}
	else if (lx < posx) {
		if (ly > - lx && ly > posy) return 1;
		else if (ly < lx && ly < posy) return 3;
		else if (ly < - lx && ly > lx) return 4;
	}
	else if (lx == posx) {
		if (ly <= posy) return 3;
		else return 1;
	}
	

}
