///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//
//  model data
///////////////////////////////////////////////////////////////////

//  world geometry
// eye    (0,0,0)
// center (0,0,-1)
// up     (0,1,0)
// left -1, right 1
//  top & bottom centered on Y to match the window aspect ratio
// clipping planes: 1, 5.1

#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <math.h>
#include "stanza.h"
#include"Marine.h"

#define PI 3.141592654
using std::vector;
// A class for storing vetices
//  Vertex
class Vertex {
public:

	float x, y, z;     // 3d coordinate of the vertex
	float Nx, Ny, Nz;     // Normal to the surface (if present)
	float u, v;						// texture coordinates
	float r, g, b;				// Color (0.0 -  1.0)

	Vertex() {}
	Vertex(float x, float y, float z) : x(x), y(y), z(z) { }
	Vertex(float x, float y, float z, float u, float v) : x(x), y(y), z(z),
		u(u), v(v) { }
	inline void SetP(float x, float y, float z) {
		this->x = x; this->y = y;
		this->z = z;
	}
	inline void SetN(float x, float y, float z) { Nx = x; Ny = y; Nz = z; }
};


class MyModel {
public:
	//  general data for window and input controls
	HDC			hDC;		        // Private GDI Device Context
	HGLRC		hRC;		        // Permanent Rendering Context
	HWND		hWnd;		        // Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application

	bool	keys[256];			// Array Used For The Keyboard Routine
	bool	active;		      // Window Active Flag Set To TRUE By Default
	bool	fullscreen;	    // Fullscreen Flag 
	int temp;

private:
	//  projection limits in X and Y: x in [-plx, plx], y in [-ply, ply]
	double plx, ply;
	int Wheight, Wwidth;  // window dimensions in pixels
	int frames;           // n. of frames
	double frameTime;     // for fps computation
	double fps;
	Marine marine;
	Vertex p;
	stanza room;
	//  model data
	std::vector<Vertex> Background;   // background
	
	clock_t Tstamp, Tstart;
	double Full_elapsed;  // elapsed time in seconds from the beginning of the program

	GLuint	texture[28];			// Storage For 28 Textures!
	GLuint	base;				// Base Display List For The Font Set
public:
	//  methods
	MyModel() : hDC(NULL), hRC(NULL), hWnd(NULL), active(true),
		fullscreen(true), frames(0), fps(0) {
		float cellx = 2.0 / 6;
		Background.clear();  //16 vertici
		float x = -1.0f -(1.0f/3);
		float y = -1.0f;
		float celly = 2.0 / 4;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				Background.push_back(Vertex(x, y, -5, 0, 0));
				Background.push_back(Vertex(x+cellx, y, -5, 1, 0));
				Background.push_back(Vertex(x+cellx, y+celly, -5, 1, 1));
				Background.push_back(Vertex(x, y+celly, -5, 0, 1));
				y = y + celly;
			}
			x = x + cellx;
			y = -1.0f;
		}
		p = Vertex (0, -1+0.08f, -5);
		this->marine.setPosition(0, -1);
		/*Background.push_back(Vertex(-1, -1, -5, 0, 0));	//primo rett
		Background.push_back(Vertex(-cell, -1, -5, 1, 0));
		Background.push_back(Vertex(-cell, 0, -5, 1, 1));
		Background.push_back(Vertex(-1, 0, -5, 0, 1));

		Background.push_back(Vertex(-cell, -1, -5, 0, 0)); //secondo rett
		Background.push_back(Vertex(cell, -1, -5, 1, 0));
		Background.push_back(Vertex(cell, 0, -5, 1, 1));
		Background.push_back(Vertex(-cell, 0, -5, 0, 1));

		Background.push_back(Vertex(cell, -1, -5, 0, 0)); //terzo rett
		Background.push_back(Vertex(1, -1, -5, 1, 0));
		Background.push_back(Vertex(1, 0, -5, 1, 1));
		Background.push_back(Vertex(cell, 0, -5, 0, 1));
		
		Background.push_back(Vertex(cell, 0, -5, 0, 0)); //quarto rett
		Background.push_back(Vertex(1, 0, -5, 1, 0));
		Background.push_back(Vertex(1, 1, -5, 1, 1));
		Background.push_back(Vertex(cell, 1, -5, 0, 1));
		
		Background.push_back(Vertex(-cell, 0, -5, 0, 0)); //quinto rett
		Background.push_back(Vertex(cell, 0, -5, 1, 0));
		Background.push_back(Vertex(cell, 1, -5, 1, 1));
		Background.push_back(Vertex(-cell, 1, -5, 0, 1));
		
		Background.push_back(Vertex(-1, 0, -5, 0, 0)); //sesto rett
		Background.push_back(Vertex(-cell, 0, -5, 1, 0));
		Background.push_back(Vertex(-cell, 1, -5, 1, 1));
		Background.push_back(Vertex(-1, 1, -5, 0, 1));
		*/
		
		/*this->Tstart = this->Tstamp = clock();
		this->Full_elapsed = 0;
		this->frameTime = 0;
		*/
	}
	~MyModel() {
		this->KillFont();
	}
	bool DrawGLScene(void);
	bool InitGL(void);
	void ReSizeGLScene(int width, int height);
	void glPrint(const char *fmt, ...);			// Custom GL "Print" Routine
	void move(int dir);
	void setMarineWatch(GLdouble x, GLdouble y);
	
	Marine& getMarine();
private:
	bool LoadGLTextures(void);
	void SetProjection();
	void BuildFont(void);
	void KillFont(void);
	
	//  Conversion from pixel distance to float X and Y distance
	inline float PixToCoord_X(int pix)
	{
		return (2.0f * (float)pix * (float)plx) / (float)Wwidth;
	}
	inline float PixToCoord_Y(int pix)
	{
		return (2.0f * (float)pix * (float)ply) / (float)Wheight;
	}

};

extern class MyModel Data;