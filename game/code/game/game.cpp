

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 

#include <stdio.h> 

#include <ddraw.h>  // directX includes
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusicc.h>
#include <dinput.h>

#include <softbreeze/softbreeze.h>// game library includes
#include <softbreeze/core/graphic.h>
#include <softbreeze/core/input.h>

#include <softbreeze/math/vector2.h>
#include <softbreeze/math/vector3.h>
#include <softbreeze/object/mesh.h>
#include <softbreeze/object/vertex_list.h>
#include <softbreeze/file/obj_file_loader.h>
#include <softbreeze/core/pipe_line.h>

#include "game.h"


Mesh		mesh;
VertexList	vertices;

int Game_Init(void *parms)
{
	// this function is where you do all the initialization 
	// for your game

	// start up DirectDraw (replace the parms as you desire)
	softbreeze::DDraw_Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP);

	// initialize directinput
	softbreeze::DInput_Init();

	// acquire the keyboard 
	softbreeze::DInput_Init_Keyboard();

	// add calls to acquire other directinput devices here...


	// initialize directsound and directmusic
	//DSound_Init();
	//DMusic_Init();

	// hide the mouse
	if(!WINDOWED_APP)
		ShowCursor(FALSE);

	// seed random number generator
	srand(softbreeze::Start_Clock());

	// all your initialization code goes here...
	//ObjFileLoader::Load("xxx.obj", &mesh);

	Vertex vertex1;
	vertex1.xyz.x = 0;
	vertex1.xyz.y = 0;
	vertex1.xyz.z = 100;

	Vertex vertex2;
	vertex2.xyz.x = 90;
	vertex2.xyz.y = 0;
	vertex2.xyz.z = 100;

	Vertex vertex3;
	vertex3.xyz.x = 45;
	vertex3.xyz.y = 90;
	vertex3.xyz.z = 100;

	vertices.vertices.push_back(vertex1);
	vertices.vertices.push_back(vertex2);
	vertices.vertices.push_back(vertex3);

	for(int j=0 ; j<3; j++) {
		vertices.indices.push_back(j);
	}



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
	softbreeze::DInput_Release_Keyboard();

	softbreeze::DInput_Shutdown();

	// shutdown directdraw last
	softbreeze::DDraw_Shutdown();

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
	softbreeze::Start_Clock();

	// clear the drawing surface 
	softbreeze::DDraw_Fill_Surface(softbreeze::lpddsback, 0);

	// read keyboard and other devices here
	softbreeze::DInput_Read_Keyboard();

	// game logic here...

	VertexList projectionVertices;
	softbreeze::PipeLine::Projection(vertices, projectionVertices);

	VertexList ScreenVertices;
	softbreeze::PipeLine::ToScreen(projectionVertices, WINDOW_WIDTH, WINDOW_HEIGHT, ScreenVertices);

	// lock the back buffer
	softbreeze::DDraw_Lock_Back_Surface();

	// render the polygon list
	softbreeze::PipeLine::DrawVertexList(ScreenVertices, softbreeze::back_buffer, softbreeze::back_lpitch);

	// unlock the back buffer
	softbreeze::DDraw_Unlock_Back_Surface();


	// flip the surfaces
	softbreeze::DDraw_Flip();

	// sync to 30ish fps
	softbreeze::Wait_Clock(30);

	// check of user is trying to exit
	if(KEY_DOWN(VK_ESCAPE) || softbreeze::keyboard_state[DIK_ESCAPE]) {
		PostMessage(softbreeze::main_window_handle, WM_DESTROY, 0, 0);

	} // end if

	// return success
	return(1);

} // end Game_Main