#pragma once
class Marine
{
public:
	Marine() {
		pv = 100;
		ammo = 200;
	};
	~Marine();
	void feritaSubita(int danno);
	void spara();
	void setPosition(float x, float y);
private:
	int pv;
	int ammo;
	float posx;
	float posy;

};

