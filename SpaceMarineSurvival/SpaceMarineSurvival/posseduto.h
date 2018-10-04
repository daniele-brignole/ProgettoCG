#pragma once
#include "nemico.h"
class posseduto :
	public nemico
{
public:
	posseduto(int id);
	~posseduto();

private:
	int pv;
	int id;
	float mov;
};

