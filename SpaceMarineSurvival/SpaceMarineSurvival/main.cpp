/*
*    CREDITS: this program is based on the new nehe lesson 06.
*    Modifiyed by Aldo Grattarola for the Computer Graphics course.
*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing The Base Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//  How to:
//  - load textures
//  - simulate a 2D rendering
//  - using transparency
//  - ....
/////////////////////////////////----------------------------------
//  VERSION 1: added
//  - correct timing
//  - animated textures
//  - how to write on the window
///////////////////////////////////////////////////////////////////
//  VERSION 2: added
//  - sounds via the audiere library (GNU LESSER GENERAL PUBLIC LICENSE)
//    The F2,F3 and F4 keys demonstrate the use of the mixer to add
//    sound effects
//    see audiere.sourceforge.net
//  NOTE: if you use the debug configuration copy the audiere.dll file to
//        the Debug directory!
///////////////////////////////////////////////////////////////////

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include<iostream>
#include<string>
#include "Model.h"
#include "stanza.h"


//#include "audiere.h"
#include"SOIL.h"
//using namespace audiere;
using namespace std;
//  LIBRERIE OPENGL e multimendia
//	OpenGL libraries
#pragma comment( lib, "opengl32.lib" )				// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )						// Search For GLu32.lib While Linking
//#pragma comment( lib, "winmm.lib" )						// Search For WinMM Library While Linking

stanza room;
stanza* r = &room;
class MyModel Data(r);
int temp;
int state;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

														///////////////////////////////////////////////////////////
														//  kill the window
GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (Data.fullscreen)									// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);			// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (Data.hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL)) {				// Are We Able To Release The DC And RC Contexts?
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(Data.hRC)) {			// Are We Able To Delete The RC?
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		Data.hRC = NULL;										// Set RC To NULL
	}

	if (Data.hDC && !ReleaseDC(Data.hWnd, Data.hDC)) {		// Are We Able To Release The DC
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		Data.hDC = NULL;										// Set DC To NULL
	}

	if (Data.hWnd && !DestroyWindow(Data.hWnd)) {			// Are We Able To Destroy The Window?
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		Data.hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("Basic2D", Data.hInstance))		// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		Data.hInstance = NULL;									// Set hInstance To NULL
	}
}
///////////////////////////////////////////////////////////
//  create the window
/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	Data.fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	Data.hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = Data.hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "Basic2D";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (Data.fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				Data.fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (Data.fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(Data.hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"Basic2D",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		Data.hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(Data.hDC = GetDC(Data.hWnd)))				// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(Data.hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(Data.hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(Data.hRC = wglCreateContext(Data.hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(Data.hDC, Data.hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(Data.hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(Data.hWnd);						// Slightly Higher Priority
	SetFocus(Data.hWnd);									// Sets Keyboard Focus To The Window
	Data.ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!Data.InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, SOIL_last_result(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
		
		//cout << SOIL_last_result() << endl;
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


///////////////////////////////////////////////////////////
// callback function
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	//FloatBuffer floatBuffer = ByteBuffer.allocateDirect(4).order(ByteOrder.nativeOrder()).asFloatBuffer();
	
	switch (uMsg)									// Check For Windows Messages
	{
	

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			Data.active = TRUE;
		}					// Program Is Active
		else { Data.active = FALSE; }		// Program Is No Longer Active
		return 0;								      // Return To The Message Loop
	}
	case WM_RBUTTONDOWN:
	{
		Data.getMarine().spara(2);
		break;
	}

	case WM_RBUTTONUP:
	{
		Data.getMarine().stopfire();
		break;
	}
	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{	PostQuitMessage(0);					// Send A Quit Message
	return 0;								    // Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{	Data.keys[wParam] = TRUE;		// If So, Mark It As TRUE
	return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{	Data.keys[wParam] = FALSE;	// If So, Mark It As FALSE
	return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{	Data.ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
	return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////
//  Main program
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
		
														// Init of the default button depending on Data.fullscreen
	unsigned long Def = MB_DEFBUTTON1;
	if (!Data.fullscreen) Def = MB_DEFBUTTON2;
	stanza* indirizzo = r;
	
	Data.fullscreen = false;  // removed the boring request...

							  // Create Our OpenGL Window
	if (!CreateGLWindow("Basic 2D game skeleton", 1416, 600, 16, Data.fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	//  AUDIO - start
	/*AudioDevicePtr device(OpenDevice());
	if (!device) {
		return 0;         // failure
	}
	OutputStreamPtr stream(OpenSound(device, "../Data/ophelia.mp3", true));
	if (!stream) {
		return 0;         // failure
	}
	stream->setRepeat(true);
	stream->setVolume(0.5f); // 50% volume
	stream->play();

	*/
	//  AUDIO - end

	//ShowCursor(FALSE);
	clock_t now = 0;
	clock_t last = 0;
	double remain = 0.5;
	state = 0;
	while (!done)									// Loop That Runs While done=FALSE
	{	
		//schermo iniziale
		while (state == 0) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
				{
					done = TRUE;							// If So done=TRUE
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{
				if ((Data.active && !Data.DrawIntro()) || Data.keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
				{
					done = TRUE;
					state = -1;// ESC or DrawGLScene Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					SwapBuffers(Data.hDC);					// Swap Buffers (Double Buffering)
				}
			}
			if (Data.keys['1']) {
				state = 1;
			}
			if (Data.keys['2']) {
				state = 4;
			}
		}


		//shermo gioco
		while (state == 1) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
				{
					done = TRUE;							// If So done=TRUE
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{

				room.addEnemy();
				room.gestisci();
				// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
				if ((Data.active && !Data.DrawGLScene()) || Data.keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
				{
					done = TRUE;	
					state = -1;   // ESC or DrawGLScene Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					SwapBuffers(Data.hDC);	
					if (room.isFine()) {
				state = 2;
			}
				}

			}

			if (Data.keys['W']) {
				//Data.getMarine().setRivolto(3);
				Data.move(0);
			}
			if (Data.keys['D']) {
				Data.move(1);
			}
			if (Data.keys['S']) {
				//Data.getMarine().setRivolto(1);
				Data.move(2);
			}
			if (Data.keys['A']) {
				//Data.getMarine().setRivolto(4);
				Data.move(3);
			}
			now = clock();
			if (remain < 0 || last > 0) {
				remain = (double)(now - last) / (double)CLOCKS_PER_SEC;
			}
			if (Data.keys[VK_RIGHT] && remain >= 0.5) {
				last = clock();
				Data.getMarine().setRivolto(2);
				Data.getMarine().spara(1);
				remain = 1;

			}
			if (Data.keys[VK_LEFT] && remain >= 0.5) {
				last = clock();
				Data.getMarine().setRivolto(4);
				Data.getMarine().spara(3);
				remain = 1;
			}
			if (Data.keys[VK_UP] && remain >= 0.5) {
				last = clock();
				Data.getMarine().setRivolto(3);
				Data.getMarine().spara(0);
				remain = 1;
			}
			if (Data.keys[VK_DOWN] && remain >= 0.5) {
				last = clock();
				Data.getMarine().setRivolto(1);
				Data.getMarine().spara(2);
				remain = 1;
				
			}
			if (room.isFine()) {
				state = 2;
			}
			if (Data.getMarine().getPv() <= 0) {
				state = 3;
			}
		}
		//schermata livello completato
		while (state == 2) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
				{
					done = TRUE;							// If So done=TRUE
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{
				if ((Data.active && !Data.DrawEnd(29)) || Data.keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
				{
					done = TRUE;
					state = -1;// ESC or DrawGLScene Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					SwapBuffers(Data.hDC);					// Swap Buffers (Double Buffering)
				}
			}
			if (Data.keys['E']) {
				state = 0;
				room.reset();
				Data.getMarine().reset();
			}
		}
		//schermata game over
		while (state == 3) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
				{
					done = TRUE;							// If So done=TRUE
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{
				if ((Data.active && !Data.DrawEnd(30)) || Data.keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
				{
					done = TRUE;
					state = -1;// ESC or DrawGLScene Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					SwapBuffers(Data.hDC);					// Swap Buffers (Double Buffering)
				}
			}
			if (Data.keys['E']) {
				state = 0;
				room.reset();
				Data.getMarine().reset();
			}
		}
		//schermata comandi
		while (state == 4) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
			{
				if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
				{
					done = TRUE;							// If So done=TRUE
				}
				else									// If Not, Deal With Window Messages
				{
					TranslateMessage(&msg);				// Translate The Message
					DispatchMessage(&msg);				// Dispatch The Message
				}
			}
			else										// If There Are No Messages
			{
				if ((Data.active && !Data.DrawEnd(31)) || Data.keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
				{
					done = TRUE;
					state = -1;// ESC or DrawGLScene Signalled A Quit
				}
				else									// Not Time To Quit, Update Screen
				{
					SwapBuffers(Data.hDC);					// Swap Buffers (Double Buffering)
				}
			}
			if (Data.keys['E']) {
				state = 0;
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

