#pragma once

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
	void spara();
	void setPosition(float x, float y);
	void setLoS(float x, float y);
	float getLosx();
	float getLosy();
	int calcolaVisuale();
private:
	int pv;
	int ammo;
	float posx;
	float posy;
	int rivolto;
	float losx, losy;

};

