

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 

#include <stdio.h> 

#include <ddraw.h>  // directX includes
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusicc.h>
#include <dinput.h>

#include <softbreeze_graphic.h>// game library includes
#include <softbreeze_input.h>

#include "game.h"


int Game_Init(void *parms)
{
	// this function is where you do all the initialization 
	// for your game

	// start up DirectDraw (replace the parms as you desire)
	DDraw_Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP);

	// initialize directinput
	DInput_Init();

	// acquire the keyboard 
	DInput_Init_Keyboard();

	// add calls to acquire other directinput devices here...


	// initialize directsound and directmusic
	//DSound_Init();
	//DMusic_Init();

	// hide the mouse
	if(!WINDOWED_APP)
		ShowCursor(FALSE);

	// seed random number generator
	srand(Start_Clock());

	// all your initialization code goes here...


	// return success
	return(1);

} // end Game_Init

///////////////////////////////////////////////////////////

int Game_Shutdown(void *parms)
{
	// this function is where you shutdown your game and
	// release all resources that you allocated

	// shut everything down

	// release all your resources created for the game here....


	// now directsound
	//DSound_Stop_All_Sounds();
	//DSound_Delete_All_Sounds();
	//DSound_Shutdown();

	// directmusic
	//DMusic_Delete_All_MIDI();
	//DMusic_Shutdown();

	// shut down directinput
	DInput_Release_Keyboard();

	DInput_Shutdown();

	// shutdown directdraw last
	DDraw_Shutdown();

	// return success
	return(1);
} // end Game_Shutdown

//////////////////////////////////////////////////////////

int Game_Main(void *parms)
{
	// this is the workhorse of your game it will be called
	// continuously in real-time this is like main() in C
	// all the calls for you game go here!

	int index; // looping var

	// start the timing clock
	Start_Clock();

	// clear the drawing surface 
	DDraw_Fill_Surface(lpddsback, 0);

	// read keyboard and other devices here
	DInput_Read_Keyboard();

	// game logic here...



	// flip the surfaces
	DDraw_Flip();

	// sync to 30ish fps
	Wait_Clock(30);

	// check of user is trying to exit
	if(KEY_DOWN(VK_ESCAPE) || keyboard_state[DIK_ESCAPE]) {
		PostMessage(main_window_handle, WM_DESTROY, 0, 0);

	} // end if

	// return success
	return(1);

} // end Game_Main