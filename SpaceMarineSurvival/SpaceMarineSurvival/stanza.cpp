#include "stanza.h"



stanza::stanza()
{
	float x = 
	contaround = 3;
	top = 1;
	bot = -1;
	left = -1.0f - (1.0f / 3);
	right = 1.0f + (1.0f / 3);
}



bool stanza::isMovePossible(int dir,float nextpos)
{
	switch (dir) {
	case 0:
		if (nextpos > top) return false;
		break;
	case 1:
		if (nextpos > right) return false;
		break;
	case 2:
		if (nextpos < bot) return false;
		break;
	case 3:
		if (nextpos < left) return false;
		break;
	}
	return true;
}

