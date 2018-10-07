#include "stanza.h"



stanza::stanza()
{
	ostacolo1.x = 0.5;
	ostacolo1.y = 0.5;

	ostacolo2.x = -0.5;
	ostacolo2.y = -0.5;
	ostacoli.push_back(ostacolo1);
	ostacoli.push_back(ostacolo2);
	
	contanemici = 0;
	contaround = 1;
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
		if (x > ostacoli[i].x - 0.1 && x < ostacoli[i].x + 0.1 && y > ostacoli[i].y - 0.1&& y < ostacoli[i].y + 0.1) return true;
	}
	return false;
}
std::vector<ostacolo>& stanza::getOstacoli() {
	return ostacoli;
}

void stanza::addEnemy()
{
	if (contanemici < 5) {
		contanemici++;
		nemico n = generaNemico();
		nemici.push_back(n);
	}
}

nemico stanza::generaNemico()
{
	//int newNumber = (rand() % (contaround)) + 1;
	//int newNumber = static_cast<double>(std::rand()) / RAND_MAX * contaround + 1;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, contaround);
	int newNumber = distr(eng);
	switch (newNumber) {
	case 1:
		return cultista(1);
		break;
	case 2:
		return chmarine(1);
		break;
	case 3:
		return posseduto(1);
		break;
	}
}

void stanza::gestisci()
{
	for (int i = 0; i < nemici.size(); i++) {
		if (nemici[i].getId() == 0) {
			nemici[i].decidi();
		}
		else nemici[i].move();
	}
}

std::vector<nemico>& stanza::getNemici() {
	return nemici;
}
