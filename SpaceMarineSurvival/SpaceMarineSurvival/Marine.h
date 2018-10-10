#pragma once

#include <vector>
#include"stanza.h"

using std::vector;
struct shot {
	float x;
	float y;
	int dir;
};

class Marine
{
public:
	Marine();
	Marine(stanza* stz) {
		this->stz = stz;
		pv = 100;
		ammo = 200;
		rivolto = 1;
		//losx = 0; losy = 0;
	};
	~Marine();
	void feritaSubita(int danno);
	float spara(int x);
	void setPosition(float x, float y);
	void setLoS(float x, float y);
	void setIsFiring();
	bool isFiring();
	void stopfire();
	int getRivolto();
	float getLosx();
	float getLosy();
	void incrementshot();
	void setRivolto(int val);
	float getPosx();
	float getPosy();
private:
	int pv;
	int ammo;
	bool isShooting;
	vector<shot> onScreenShoot;
	stanza* stz;
	float posx;
	float posy;
	int rivolto;
	float losx, losy;
public:
	vector<shot>& getOnScreenShoot();
};

