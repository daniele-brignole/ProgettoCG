#pragma once
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include<iostream>
#include<string>
class stanza
{
public:
	stanza();
	stanza(int lunghezza, int altezza);
	bool isMovePossible(int dir,float nextpos);
private:
	int lunghezza, altezza;
	int contaround;
	int contanemici;
	float top,bot,right,left;
	
};
