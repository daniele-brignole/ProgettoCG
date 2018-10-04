#pragma once
#include "nemico.h"
class chmarine :
	public nemico
{
public:
	chmarine(int id);
	~chmarine();

private:
	int id;
	int pv;
	float mov;
};

