///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//
//  model data
///////////////////////////////////////////////////////////////////

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <vector>
#include "Model.h"
#include "stanza.h"
#include "SOIL.h"
#include<string>

// All Setup For OpenGL Goes Here
bool MyModel::InitGL(void)
{
	if (!this->LoadGLTextures())				// Jump To Texture Loading Routine
	{
		return false;
	}							// If Texture Didn't Load Return FALSE


	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	this->BuildFont();

	// eye    (0,0,0)
	// center (0,0,-1)
	// up     (0,1,0)
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//double ix = ((1400 + 0.5) / 2) / atan(22.5* PI / 180.0);
	
	return true;										// Initialization Went OK
}


void MyModel::ReSizeGLScene(int width, int height)
{
	if (height == 0) height = 1;					// Prevent A Divide By Zero By
	if (width == 0) width = 1;					// Prevent A Divide By Zero By

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// orthographic projection
														// background in [-1, 1] on both x and y
														// fill th background according to the window aspect ratio
														// void WINAPI glOrtho( GLdouble left,   GLdouble right,
														//                      GLdouble bottom, GLdouble top,
														//                      GLdouble zNear,  GLdouble zFar );
	if (width >= height) {
		this->plx = 1.0;
		this->ply = (double)height / (double)width;
	}
	else {
		this->plx = (double)width / (double)height;
		this->ply = 1.0;
	}
	glOrtho(-this->plx, this->plx, -this->ply, this->ply, 1, 5.1);

	//  saving the window width and height in pixels
	this->Wheight = height;
	this->Wwidth = width;

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}



// Load Bitmaps And Convert To Textures
bool MyModel::LoadGLTextures(void)
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
	("../textures/metal_floor.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[0] == 0) return false;
	
	texture[1] = SOIL_load_OGL_texture
	("../textures/marine_1.TGA",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[1] == 0) return false;
	
	texture[2] = SOIL_load_OGL_texture(
		"../textures/marine_2.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[2] == 0) return false;
	
	texture[3] = SOIL_load_OGL_texture(
		"../textures/marine_3.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[3] == 0) return false;

	texture[4] = SOIL_load_OGL_texture(
		"../textures/marine_4.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[4] == 0) return false;
	
	texture[5] = SOIL_load_OGL_texture(
		"../textures/shot_down.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[5] == 0) return false;

	texture[6] = SOIL_load_OGL_texture(
		"../textures/shot.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[6] == 0) return false;

	texture[7] = SOIL_load_OGL_texture(
		"../textures/shot_up.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[7] == 0) return false;

	texture[8] = SOIL_load_OGL_texture(
		"../textures/shot_left.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[8] == 0) return false;

	texture[9] = SOIL_load_OGL_texture(
		"../textures/blocco.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[9] == 0) return false;
	
	texture[10] = SOIL_load_OGL_texture(
		"../textures/cultista.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[10] == 0) return false;

	texture[11] = SOIL_load_OGL_texture(
		"../textures/cultista_2.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[11] == 0) return false;

	texture[12] = SOIL_load_OGL_texture(
		"../textures/chMarine_1.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[12] == 0) return false;

	texture[13] = SOIL_load_OGL_texture(
		"../textures/chMarine_2.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[13] == 0) return false;

	texture[14] = SOIL_load_OGL_texture(
		"../textures/chMarine_3.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[14] == 0) return false;

	texture[15] = SOIL_load_OGL_texture(
		"../textures/chMarine_4.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[15] == 0) return false;

	texture[16] = SOIL_load_OGL_texture(
		"../textures/posseduto_1.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[16] == 0) return false;

	texture[17] = SOIL_load_OGL_texture(
		"../textures/chMarine_4.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[15] == 0) return false;

	texture[18] = SOIL_load_OGL_texture(
		"../textures/laser.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[18] == 0) return false;
	
	texture[19] = SOIL_load_OGL_texture(
		"../textures/rubricBolt.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[19] == 0) return false;
	
	texture[20] = SOIL_load_OGL_texture(
		"../textures/graffio1.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[20] == 0) return false;

	texture[21] = SOIL_load_OGL_texture(
		"../textures/graffio2.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[21] == 0) return false;

	texture[22] = SOIL_load_OGL_texture(
		"../textures/graffio3.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[22] == 0) return false;

	texture[23] = SOIL_load_OGL_texture(
		"../textures/graffio4.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[23] == 0) return false;

	texture[24] = SOIL_load_OGL_texture(
		"../textures/graffio5.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[24] == 0) return false;

	texture[25] = SOIL_load_OGL_texture(
		"../textures/graffio6.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[25] == 0) return false;

	texture[26] = SOIL_load_OGL_texture(
		"../textures/graffio7.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[26] == 0) return false;

	texture[27] = SOIL_load_OGL_texture(
		"../textures/graffio8.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[27] == 0) return false;
	texture[28] = SOIL_load_OGL_texture(
		"../textures/TitleScreen.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[28] == 0) return false;
	texture[29] = SOIL_load_OGL_texture(
		"../textures/fine.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[29] == 0) return false;
	
	texture[30] = SOIL_load_OGL_texture(
		"../textures/gameover.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[30] == 0) return false;

	texture[31] = SOIL_load_OGL_texture(
		"../textures/comandi.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[31] == 0) return false;

	texture[32] = SOIL_load_OGL_texture(
		"../textures/boom.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[32] == 0) return false;

	/*texture[33] = SOIL_load_OGL_texture(
		"../textures/boom2.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[33] == 0) return false;

	texture[34] = SOIL_load_OGL_texture(
		"../textures/boom3.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[34] == 0) return false;
	
	texture[35] = SOIL_load_OGL_texture(
		"../textures/boom4.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[35] == 0) return false;

	texture[36] = SOIL_load_OGL_texture(
		"../textures/boom5.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[36] == 0) return false;

	texture[37] = SOIL_load_OGL_texture(
		"../textures/boom6.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[37] == 0) return false;

	texture[38] = SOIL_load_OGL_texture(
		"../textures/boom7.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (texture[38] == 0) return false;
	*/
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;										// Return Success
}
void MyModel::SetProjection()
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	
		double Far = 2.0 * 1400;
		
		gluPerspective(25.0, (GLfloat)1416 / (GLfloat)600, 0.001, Far);
		
		gluLookAt(0, 0, 0, 0, 0, -1, 0.0, 1.0, 0.0);
	
}



bool MyModel::DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The View

	this->SetProjection();
														//  TIMING - start
	clock_t t = clock();
	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;
	
	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);
	// elapsed time in seconds from the beginning of the program
	this->Full_elapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	this->Tstamp = t;
	//  TIMING - end

	
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glColor4f(0.0, 0.0, 0.0,1.0);
	//  Background
	glBegin(GL_QUADS);
	for (int i = 0; i < Background.size(); i++) {
		glTexCoord2f(Background[i].u, Background[i].v);
		glNormal3f(0, 0, 1.0f);
		glVertex3f(Background[i].x, Background[i].y, Background[i].z);
	}
	glEnd();
	//texture marine
	int rivolto = marine.getRivolto();
	glBindTexture(GL_TEXTURE_2D, texture[rivolto]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(p.x-0.05f,p.y-0.05f,p.z);
	
	glTexCoord2f(1,0);
	glVertex3f(p.x+0.05f,p.y-0.05f,p.z);
	
	glTexCoord2f(1,1);
	glVertex3f(p.x + 0.05f,p.y+0.05f,p.z);
	
	glTexCoord2f(0,1);
	glVertex3f(p.x -0.05f, p.y+0.05f, p.z);
	glEnd();
	
	
	
	//generazione ostacoli
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	std::vector<ostacolo> blocchi = room->getOstacoli();
	for (int b = 0; b < blocchi.size(); b++) {
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(blocchi[b].x-0.1, blocchi[b].y - 0.1, -5.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(blocchi[b] .x+ 0.1, blocchi[b].y -0.1, -5.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(blocchi[b].x + 0.1, blocchi[b].y + 0.1, -5.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(blocchi[b].x - 0.1, blocchi[b].y + 0.1, -5.0);
		glEnd();
	}
	//texture colpi
	this->marine.incrementshot();
	vector<shot> temp = this->marine.getOnScreenShoot();
	E_shot e;
	int s = max(temp.size(), room->getShotSize());
	for (int i = 0; i < s; i++) {
		if (i < temp.size()) {
			glBindTexture(GL_TEXTURE_2D, texture[rivolto + 4]);


			glBegin(GL_QUADS);

			glTexCoord2f(0.0, 0.0);
			glVertex3f(temp[i].x - 0.03, temp[i].y - 0.03, -5.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(temp[i].x + 0.03, temp[i].y - 0.03, -5.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(temp[i].x + 0.03, temp[i].y + 0.03, -5.0);

			glTexCoord2f(0.0, 1.0);
			glVertex3f(temp[i].x - 0.03, temp[i].y + 0.03, -5.0);
			glEnd();
		}
		if (i < room->getShotSize()) {
			e = room->updateShots(i);
			if(room->checkMarineCollision(e.nowx, e.nowy, 0.03)) this->marine.feritaSubita(1);
			glBindTexture(GL_TEXTURE_2D, texture[e.type]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(e.nowx - 0.03f, e.nowy - 0.03f, -5);

			glTexCoord2f(1, 0);
			glVertex3f(e.nowx + 0.03f, e.nowy - 0.03f, p.z);

			glTexCoord2f(1, 1);
			glVertex3f(e.nowx + 0.03f, e.nowy + 0.03f, p.z);

			glTexCoord2f(0, 1);
			glVertex3f(e.nowx - 0.03f, e.nowy + 0.03f, p.z);
			glEnd();
			if (e.erase) room->eraseShot(i);
		}
	}
	//texture nemici
	std::vector<nemico> NMI = room->getNemici();
	
	int texF = 0;
	for (int i = 0; i < NMI.size(); i++) {
		if (NMI[i].isMorto()) {
			glBindTexture(GL_TEXTURE_2D, texture[32]);
			for (int k = 0; k < 7 ; k++) {
				double j = (k / 7.0) ;
				double h = (k+1) / 7.0 ;
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glBegin(GL_QUADS);
				glTexCoord2f(j, 0);
				glVertex3f(NMI[i].getPosx() - 0.05f, NMI[i].getPosy() - 0.05f, p.z);

				glTexCoord2f(h, 0);
				glVertex3f(NMI[i].getPosx() + 0.05f, NMI[i].getPosy() - 0.05f, p.z);

				glTexCoord2f(h, 1);
				glVertex3f(NMI[i].getPosx() + 0.05f, NMI[i].getPosy() + 0.05f, p.z);

				glTexCoord2f(j, 1);
				glVertex3f(NMI[i].getPosx() - 0.05f, NMI[i].getPosy() + 0.05f, p.z);
				glEnd();
				//SwapBuffers(this->hDC);
				//
			}
			room->eraseEnemy(i);
		}
		
		else {
			glBindTexture(GL_TEXTURE_2D, texture[NMI[i].getVerso()]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(NMI[i].getPosx() - 0.05f, NMI[i].getPosy() - 0.05f, p.z);

			glTexCoord2f(1, 0);
			glVertex3f(NMI[i].getPosx() + 0.05f, NMI[i].getPosy() - 0.05f, p.z);

			glTexCoord2f(1, 1);
			glVertex3f(NMI[i].getPosx() + 0.05f, NMI[i].getPosy() + 0.05f, p.z);

			glTexCoord2f(0, 1);
			glVertex3f(NMI[i].getPosx() - 0.05f, NMI[i].getPosy() + 0.05f, p.z);
			glEnd();
			now = clock();
			if (remain < 0 || last > 0) {
				remain = (double)(now - last) / (double)CLOCKS_PER_SEC;
			}
			if (NMI[i].getAttack() && remain >= 2.0) {
				last = clock();
				this->marine.feritaSubita(5);
				texF = 20 + ((int((last * 19))) % 8);
				//for (int l = 20; l < 28; l++) {
				glBindTexture(GL_TEXTURE_2D, texture[texF]);
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0);
				glVertex3f(p.x - 0.08f, p.y - 0.08f, p.z);

				glTexCoord2f(1, 0);
				glVertex3f(p.x + 0.08f, p.y - 0.08f, p.z);

				glTexCoord2f(1, 1);
				glVertex3f(p.x + 0.08f, p.y + 0.08f, p.z);

				glTexCoord2f(0, 1);
				glVertex3f(p.x - 0.08f, p.y + 0.08f, p.z);
				glEnd();
				//}
				remain = -1;
			}
		}
	}
	
	
	glDisable(GL_ALPHA_TEST);

	// Reset The Current Modelview Matrix
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_BLEND);
	
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();
	//  Some text
	
	
	// Color
	glColor3f(0.0f, 1.0f, 0.0f);

	// Position The Text On The Screen
	glRasterPos3f(-(float)plx - PixToCoord_X(600), (float)ply - PixToCoord_Y(21),
		-4);

	// compute fps and write text
	/*this->frames++;
	if (this->frames > 18) {
		this->fps = frames / frameTime;
		this->frames = 0; this->frameTime = 0;
	}*/
	int health = this->getMarine().getPv();
	int round = room->GetContaround();
	int remaining = room->getWave(round);
	this->glPrint("Wave: %d",
		round);
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-(float)plx - PixToCoord_X(600), (float)ply + PixToCoord_Y(200),
		-4);
	this->glPrint("Health: %d",
		health);
	/*	
	if (this->Full_elapsed < 6) {
		glRasterPos3f(-(float)plx + PixToCoord_X(10), (float)-ply + PixToCoord_Y(21),
			-4);
		this->glPrint("F2/F3/F4 for sounds");
	}
	*/
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	return true;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//  bitmap fonts
void MyModel::BuildFont(void)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(-20,							// Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_BOLD,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void MyModel::KillFont(void)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

void MyModel::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

/*
	0 --- up
	1 --- right
	2 --- down
	3 --- left
*/
void MyModel::move(int dir)
{
	switch (dir) {
	case 0:
		if (room->isMovePossible(dir, p.y + 0.003f,p.x)) {
			p.y = p.y + 0.003f;
			this->marine.setPosition(p.x, p.y);
			this->room->setMarx(p.x);
			this->room->setMary(p.y);
		}
		break;
	case 1:
		if (room->isMovePossible(dir, p.x + 0.003f,p.y)) {
			p.x = p.x + 0.003f;
			this->marine.setPosition(p.x, p.y);
			this->room->setMarx(p.x);
			this->room->setMary(p.y);
		}
		break;
	case 2:
		if (room->isMovePossible(dir, p.y - 0.003f,p.x)) {
			p.y = p.y - 0.003f;
			this->marine.setPosition(p.x, p.y);
			this->room->setMarx(p.x);
			this->room->setMary(p.y);
		}
		break;
	case 3:
		if (room->isMovePossible(dir, p.x - 0.003f,p.y)) {
			p.x = p.x - 0.003f;
			this->marine.setPosition(p.x, p.y);
			this->room->setMarx(p.x);
			this->room->setMary(p.y);
		}
		break;
	}
	
}

void MyModel::setMarineWatch(GLdouble x, GLdouble y)
{
	this->marine.setLoS(x, y);
}
void MyModel::SetProjectionIntro() {
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix


	double Far = 2.0 * 1400;

	gluPerspective(25.0, (GLfloat)1416 / (GLfloat)600, 0.001, Far);

	gluLookAt(0, 0, 0, 0, 0, -1, 0.0, 1.0, 0.0);
}


bool MyModel::DrawIntro(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);	// Reset The View
	RECT r;
	this->SetProjectionIntro();
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(0, 1, 0, 1, -1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[28]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-PixToCoord_X(1416), -PixToCoord_Y(600), -5);

	glTexCoord2f(1, 0);
	glVertex3f(PixToCoord_X(1416), -PixToCoord_Y(600), -5);

	glTexCoord2f(1, 1);
	glVertex3f(PixToCoord_X(1416), PixToCoord_Y(600), -5);

	glTexCoord2f(0, 1);
	glVertex3f(-PixToCoord_X(1416), PixToCoord_Y(600), -5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	return true;
}


	Marine& MyModel::getMarine()
	{
		return this->marine;
	}

	bool MyModel::DrawEnd(int text)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
		glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);	// Reset The View
		RECT r;
		this->SetProjectionIntro();
		//glMatrixMode(GL_PROJECTION);
		//glOrtho(0, 1, 0, 1, -1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[text]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-PixToCoord_X(1416), -PixToCoord_Y(600), -5);

		glTexCoord2f(1, 0);
		glVertex3f(PixToCoord_X(1416), -PixToCoord_Y(600), -5);

		glTexCoord2f(1, 1);
		glVertex3f(PixToCoord_X(1416), PixToCoord_Y(600), -5);

		glTexCoord2f(0, 1);
		glVertex3f(-PixToCoord_X(1416), PixToCoord_Y(600), -5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		return true;
	}
