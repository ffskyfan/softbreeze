// T3DCONSOLE2.CPP - First Template for Tricks 3D Volume II
// Use this as a template for your applications if you wish
// you may want to change things like the resolution of the
// application, if it's windowed, the directinput devices
// that are acquired and so forth...
// currently the app creates a 640x480x16 windowed display
// hence, you must be in 16 bit color before running the application
// if you want fullscreen mode then simple change the WINDOWED_APP
// value in the #defines below value to FALSE (0). Similarly, if
// you want another bitdepth, maybe 8-bit for 256 colors then 
// change that in the call to DDraw_Init() in the function
// Game_Init() within this file.

// READ THIS!
// To compile make sure to include DDRAW.LIB, DSOUND.LIB,
// DINPUT.LIB, WINMM.LIB in the project link list, and of course 
// the C++ source modules T3DLIB1.CPP,T3DLIB2.CPP, and T3DLIB3.CPP
// and the headers T3DLIB1.H,T3DLIB2.H, and T3DLIB3.H must
// be in the working directory of the compiler

// INCLUDES ///////////////////////////////////////////////


#define INITGUID       // make sure all the COM interfaces are available
// instead of this you can include the .LIB file
// DXGUID.LIB

#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>

#include <ddraw.h>  // directX includes
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusicc.h>
#include <dinput.h>

#include <softbreeze/softbreeze.h>// game library includes
#include <softbreeze/core/graphic.h>
#include <softbreeze/core/input.h>

#include "game/game.h"


// DEFINES ////////////////////////////////////////////////


// PROTOTYPES /////////////////////////////////////////////


// GLOBALS ////////////////////////////////////////////////

HWND softbreeze::main_window_handle = NULL; // save the window handle
HINSTANCE softbreeze::main_instance = NULL; // save the instance
char buffer[256];                          // used to print text



// FUNCTIONS //////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   // handle to a device context

	// what is the message 
	switch(msg) {
	case WM_CREATE:
	{
		// do initialization stuff here
		return(0);
	} break;

	case WM_PAINT:
	{
		// start painting
		hdc = BeginPaint(hwnd, &ps);

		// end painting
		EndPaint(hwnd, &ps);
		return(0);
	} break;

	case WM_DESTROY:
	{
		// kill the application			
		PostQuitMessage(0);
		return(0);
	} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

// WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)
{
	// this is the winmain function
	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hwnd;	 // generic window handle
	MSG		   msg;		 // generic message
	HDC        hdc;      // graphics device context

	// first fill in the window class stucture
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC |
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if(!RegisterClassEx(&winclass))
		return(0);

	// create the window
	if(!(hwnd = CreateWindowEx(NULL,              // extended style
		WINDOW_CLASS_NAME, // class
		WINDOW_TITLE, // title
		(WINDOWED_APP ? (WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION) : (WS_POPUP | WS_VISIBLE)),
		0, 0,	  // initial x,y
		WINDOW_WIDTH, WINDOW_HEIGHT,  // initial width, height
		NULL,	  // handle to parent 
		NULL,	  // handle to menu
		hinstance,// instance of this application
		NULL)))   // extra creation parms
		return(0);

	// save the window handle and instance in a global
	softbreeze::main_window_handle = hwnd;
	softbreeze::main_instance = hinstance;

	// resize the window so that client is really width x height
	if(WINDOWED_APP) {
		// now resize the window, so the client area is the actual size requested
		// since there may be borders and controls if this is going to be a windowed app
		// if the app is not windowed then it won't matter
		RECT window_rect = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };


		// make the call to adjust window_rect
		AdjustWindowRectEx(&window_rect,
			GetWindowStyle(softbreeze::main_window_handle),
			GetMenu(softbreeze::main_window_handle) != NULL,
			GetWindowExStyle(softbreeze::main_window_handle));

		// save the global client offsets, they are needed in DDraw_Flip()
		softbreeze::window_client_x0 = -window_rect.left;
		softbreeze::window_client_y0 = -window_rect.top;

		// now resize the window with a call to MoveWindow()
		MoveWindow(softbreeze::main_window_handle,
			0, // x position
			0, // y position
			window_rect.right - window_rect.left, // width
			window_rect.bottom - window_rect.top, // height
			FALSE);

		// show the window, so there's no garbage on first render
		ShowWindow(softbreeze::main_window_handle, SW_SHOW);
	} // end if windowed

	// perform all game console specific initialization
	Game_Init();

	// enter main event loop
	while(1) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// test if this is a quit
			if(msg.message == WM_QUIT)
				break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if

		// main game processing goes here
		Game_Main();

	} // end while

	// shutdown game and release all resources
	Game_Shutdown();


	// return to Windows like this
	return(msg.wParam);

} // end WinMain

// T3D II GAME PROGRAMMING CONSOLE FUNCTIONS ////////////////


//////////////////////////////////////////////////////////