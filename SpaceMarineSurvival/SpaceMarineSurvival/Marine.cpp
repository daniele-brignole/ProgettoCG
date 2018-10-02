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
void Marine::setIsFiring()
{
	isShooting = true;
}bool Marine::isFiring()
{
	
	return isShooting;
}
float Marine::spara(int x)
{
	shot temp;
	temp.x = posx + 0.03;
	temp.y = posy;
	temp.dir = x;
	onScreenShoot.push_back(temp);
	//int d = onScreenShoot.size();
	return 1;
}
void Marine::stopfire()
{
	isShooting = false;
}
float Marine::getLosx() {
	return this->losx;
}

float Marine::getLosy()
{
	return losy;
}




float Marine::getPosx()
{
	return this->posx;
}

float Marine::getPosy()
{
	return this->posy;
}

vector<shot>& Marine::getOnScreenShoot()
{
	return onScreenShoot;
}

void Marine::incrementshot() {
	//vector<shot>::iterator itr = onScreenShoot.begin();
	int dir;
	for (int i = 0; i < onScreenShoot.size(); i++) {
		dir = onScreenShoot[i].dir;
		switch (dir) {
		case 0:
			onScreenShoot[i].y += 0.01;
			if (onScreenShoot[i].y > 1)  onScreenShoot.erase(onScreenShoot.begin() + i);
			break;
		case 1:
			onScreenShoot[i].x += 0.01;
			if (onScreenShoot[i].x > 1.30)  onScreenShoot.erase(onScreenShoot.begin() + i);
			break;
		case 2:
			onScreenShoot[i].y -= 0.01;
			if (onScreenShoot[i].y < -1.30)  onScreenShoot.erase(onScreenShoot.begin() + i);
			break;
		case 3:
			onScreenShoot[i].x -= 0.01;
			if (onScreenShoot[i].x < -1.30)  onScreenShoot.erase(onScreenShoot.begin() + i);
			break;
			
		}
		if (stz.checkCollision(onScreenShoot[i].x,onScreenShoot[i].y)) onScreenShoot.erase(onScreenShoot.begin() + i);
	}
}