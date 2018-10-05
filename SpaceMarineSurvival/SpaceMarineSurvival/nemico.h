#pragma once
#include <stdio.h>
#include<iostream>
class nemico
{
public:
	nemico();
	~nemico();
	void decidi();
	void setId(int id);
	int getId();
	float getPosx();
	float getPosy();
	void move();
private:
	int id;
	float posx, posy;
};

