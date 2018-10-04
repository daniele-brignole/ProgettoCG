#pragma once
class cultista
{
public:
	cultista();
	cultista(int id);
	~cultista();
	void move();
	int getRivolto();
	int getID();
	bool isMoving();
private:
	int id;
	int pv;
	float mov;
	int rivolto;
	bool moving;
};

