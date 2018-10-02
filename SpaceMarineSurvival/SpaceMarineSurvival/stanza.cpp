#include "stanza.h"



stanza::stanza()
{
	ostacolo1.x = 0.5;
	ostacolo1.y = 0.5;

	ostacolo2.x = -0.5;
	ostacolo2.y = -0.5;
	ostacoli.push_back(ostacolo1);
	ostacoli.push_back(ostacolo2);
	
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
		if (nextpos > top-0.05f) return false;
		break;
	case 1:
		if (nextpos > right-0.05f) return false;
		break;
	case 2:
		if (nextpos < bot+0.05f) return false;
		break;
	case 3:
		if (nextpos < left+0.05f) return false;
		break;
	}
	return true;
}

bool stanza::checkCollision(float x, float y)
{
	for (int i = 0; i < ostacoli.size(); i++) {
		if (ostacoli[i].x == x && ostacoli[i].y == y) return true;
	}
	return false;
}

