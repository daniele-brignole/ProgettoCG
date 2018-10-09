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



bool stanza::isMovePossible(int dir,float nextpos,float now)
{
	switch (dir) {
	case 0:
		if (nextpos > top-0.05f || checkCollision(now,nextpos,0.05)) return false;
		break;
	case 1:
		if (nextpos > right-0.05f || checkCollision(nextpos,now,0.05)) return false;
		break;
	case 2:
		if (nextpos < bot+0.05f || checkCollision(now,nextpos,0.05)) return false;
		break;
	case 3:
		if (nextpos < left+0.05f || checkCollision(nextpos,now,0.05)) return false;
		break;
	}
	return true;
}

bool stanza::checkCollision(float x, float y,double hitbox)
{
	for (int i = 0; i < ostacoli.size(); i++) {
		if (x + hitbox > ostacoli[i].x - 0.1 && x - hitbox < ostacoli[i].x + 0.1 && y + hitbox > ostacoli[i].y - 0.1&& y - hitbox < ostacoli[i].y + 0.1) return true;
	}
	return false;
}
std::vector<ostacolo>& stanza::getOstacoli() {
	return ostacoli;
}

void stanza::addEnemy()
{
	if (contanemici < 7) {
		contanemici++;
		nemico n = generaNemico();
		nemici.push_back(n);
	}
}

nemico stanza::generaNemico()
{
	std::random_device rd; 
	std::mt19937 eng(rd()); 
	std::uniform_int_distribution<> distr(1, contaround);
	int newNumber = distr(eng);
	switch (newNumber) {
	case 1:
		return cultista(1,this);
		break;
	case 2:
		return chmarine(1,this);
		break;
	case 3:
		return posseduto(1,this);
		break;
	}
}

void stanza::gestisci()
{
	for (int i = 0; i < nemici.size(); i++) {
		if (nemici[i].getId() == 0) {
			nemici[i].decidi();
		}
		else nemici[i].moveClose();
	}
}

std::vector<nemico>& stanza::getNemici() {
	return nemici;
}

void stanza::setMarx(double x)
{
	marx = x;
}

void stanza::setMary(double y)
{
	mary = y;
}

double stanza::getMarx()
{
	return marx;
}

double stanza::getMary()
{
	return mary;
}

void stanza::addShot(E_shot e)
{
	colpi.push_back(e);
}

E_shot& stanza::updateShots(int i)
{
	double temp = colpi[i].nowx+1;
	colpi[i].nowy = (temp - colpi[i].aimx)*(colpi[i].nowy - colpi[i].aimy) / (colpi[i].nowx - colpi[i].aimx) + colpi[i].aimy;
	colpi[i].nowx = temp;
	if (temp < -1.30 || temp >1.30 || colpi[i].nowy < -1 || colpi[i].nowy > 1) colpi[i].erase = true;
	return colpi[i];
}

int stanza::getShotSize()
{
	return colpi.size();
}

void stanza::eraseShot(int i)
{
	colpi.erase(colpi.begin() + i);
}
