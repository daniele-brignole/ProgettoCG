#pragma once
#include <vector>
using std::vector;
struct shot {
	float x;
	float y;
	int dir;
};

class Marine
{
public:
	Marine() {
		pv = 100;
		ammo = 200;
		rivolto = 0;
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
	float getLosx();
	float getLosy();
	void incrementshot();
	
	float getPosx();
	float getPosy();
private:
	int pv;
	int ammo;
	bool isShooting;
	vector<shot> onScreenShoot;
	
	float posx;
	float posy;
	int rivolto;
	float losx, losy;
public:
	vector<shot>& getOnScreenShoot();
};

