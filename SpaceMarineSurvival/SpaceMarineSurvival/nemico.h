#pragma once
class nemico
{
public:
	nemico();
	~nemico();
	int getRivolto();
	bool isMoving();
private:
	int rivolto;
	bool moving;
};

