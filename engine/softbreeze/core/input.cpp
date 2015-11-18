// T3DLIB2.CPP - Game Engine Part II

// INCLUDES ///////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  
// #define INITGUID

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <objbase.h>
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

// directX includes
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <dinput.h>

#include "../softbreeze.h"

#include "graphic.h"
#include "input.h"

softbreeze_namespace_beg

Input* Input::_inst = nullptr;


Input& Input::Instance()
{
	if(_inst == nullptr) {
		_inst = new Input;
	}

	return *_inst;
}


Input::Input()
{
	lpdi			= NULL;    // dinput object
	lpdikey			= NULL;    // dinput keyboard
	lpdimouse		= NULL;    // dinput mouse
	lpdijoy			= NULL;    // dinput joystick

	joystick_found	= 0;    // tracks if joystick was found and inited
}


Input::~Input()
{
	Release_Joystick();
	Release_Mouse();
	Release_Keyboard();
}

// FUNCTIONS //////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

namespace
{

	BOOL CALLBACK EnumJoysticks(LPCDIDEVICEINSTANCE lpddi,
								LPVOID guid_ptr)
	{
		// this function enumerates the joysticks, but
		// stops at the first one and returns the
		// instance guid of it, so we can create it
		*(GUID*)guid_ptr = lpddi->guidInstance;

		Input& input = Input::Instance();

		input.SetJoyName((char *)lpddi->tszProductName);

		// stop enumeration after one iteration
		return(DIENUM_STOP);

	} // end Input::Enum_Joysticks

}

//////////////////////////////////////////////////////////////////////////////

int Input::Init(HINSTANCE instance)
{
	// this function initializes directinput

	if(FAILED(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&lpdi, NULL)))
		return(0);

	// return success
	return(1);

} // end Input::Init

///////////////////////////////////////////////////////////

void Input::Shutdown(void)
{
	// this function shuts down directinput

	if(lpdi)
		lpdi->Release();

} // end Input::Shutdown

///////////////////////////////////////////////////////////

int Input::Init_Joystick(HWND hWnd, int min_x, int max_x, int min_y, int max_y, int dead_zone)
{
	// this function initializes the joystick, it allows you to set
	// the minimum and maximum x-y ranges 

	// first find the fucking GUID of your particular joystick
	lpdi->EnumDevices(DI8DEVCLASS_GAMECTRL,
		EnumJoysticks,
		&joystickGUID,
		DIEDFL_ATTACHEDONLY);

	// create a temporary IDIRECTINPUTDEVICE (1.0) interface, so we query for 2
	LPDIRECTINPUTDEVICE lpdijoy_temp = NULL;

	if(lpdi->CreateDevice(joystickGUID, &lpdijoy, NULL) != DI_OK)
		return(0);

	// set cooperation level
	if(lpdijoy->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
		return(0);

	// set data format
	if(lpdijoy->SetDataFormat(&c_dfDIJoystick) != DI_OK)
		return(0);

	// set the range of the joystick
	DIPROPRANGE joy_axis_range;

	// first x axis
	joy_axis_range.lMin = min_x;
	joy_axis_range.lMax = max_x;

	joy_axis_range.diph.dwSize = sizeof(DIPROPRANGE);
	joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	joy_axis_range.diph.dwObj = DIJOFS_X;
	joy_axis_range.diph.dwHow = DIPH_BYOFFSET;

	lpdijoy->SetProperty(DIPROP_RANGE, &joy_axis_range.diph);

	// now y-axis
	joy_axis_range.lMin = min_y;
	joy_axis_range.lMax = max_y;

	joy_axis_range.diph.dwSize = sizeof(DIPROPRANGE);
	joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	joy_axis_range.diph.dwObj = DIJOFS_Y;
	joy_axis_range.diph.dwHow = DIPH_BYOFFSET;

	lpdijoy->SetProperty(DIPROP_RANGE, &joy_axis_range.diph);


	// and now the dead band
	DIPROPDWORD dead_band; // here's our property word

	// scale dead zone by 100
	dead_zone *= 100;

	dead_band.diph.dwSize = sizeof(dead_band);
	dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
	dead_band.diph.dwObj = DIJOFS_X;
	dead_band.diph.dwHow = DIPH_BYOFFSET;

	// deadband will be used on both sides of the range +/-
	dead_band.dwData = dead_zone;

	// finally set the property
	lpdijoy->SetProperty(DIPROP_DEADZONE, &dead_band.diph);

	dead_band.diph.dwSize = sizeof(dead_band);
	dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
	dead_band.diph.dwObj = DIJOFS_Y;
	dead_band.diph.dwHow = DIPH_BYOFFSET;

	// deadband will be used on both sides of the range +/-
	dead_band.dwData = dead_zone;


	// finally set the property
	lpdijoy->SetProperty(DIPROP_DEADZONE, &dead_band.diph);

	// acquire the joystick
	if(lpdijoy->Acquire() != DI_OK)
		return(0);

	// set found flag
	joystick_found = 1;

	// return success
	return(1);

} // end Input::Init_Joystick

///////////////////////////////////////////////////////////

int Input::Init_Mouse(HWND hWnd)
{
	// this function intializes the mouse

	// create a mouse device 
	if(lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL) != DI_OK)
		return(0);

	// set cooperation level
	// change to EXCLUSIVE FORGROUND for better control
	if(lpdimouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
		return(0);

	// set data format
	if(lpdimouse->SetDataFormat(&c_dfDIMouse) != DI_OK)
		return(0);

	// acquire the mouse
	if(lpdimouse->Acquire() != DI_OK)
		return(0);

	// return success
	return(1);

} // end Input::Init_Mouse

///////////////////////////////////////////////////////////

int Input::Init_Keyboard(HWND hWnd)
{
	// this function initializes the keyboard device

	// create the keyboard device  
	if(lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL) != DI_OK)
		return(0);

	// set cooperation level
	if(lpdikey->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK)
		return(0);

	// set data format
	if(lpdikey->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		return(0);

	// acquire the keyboard
	if(lpdikey->Acquire() != DI_OK)
		return(0);

	// return success
	return(1);

} // end Input::Init_Keyboard

///////////////////////////////////////////////////////////

int Input::Read_Joystick(void)
{
	// this function reads the joystick state

	// make sure the joystick was initialized
	if(!joystick_found)
		return(0);

	if(lpdijoy) {
		// this is needed for joysticks only    
		if(lpdijoy->Poll() != DI_OK)
			return(0);

		if(lpdijoy->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID)&joy_state) != DI_OK)
			return(0);
	} else {
		// joystick isn't plugged in, zero out state
		memset(&joy_state, 0, sizeof(joy_state));

		// return error
		return(0);
	} // end else

	// return sucess
	return(1);

} // end Input::Read_Joystick

///////////////////////////////////////////////////////////

int Input::Read_Mouse(void)
{
	// this function reads  the mouse state

	if(lpdimouse) {
		if(lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state) != DI_OK)
			return(0);
	} else {
		// mouse isn't plugged in, zero out state
		memset(&mouse_state, 0, sizeof(mouse_state));

		// return error
		return(0);
	} // end else

	// return sucess
	return(1);

} // end Input::Read_Mouse

///////////////////////////////////////////////////////////

int Input::Read_Keyboard(void)
{
	// this function reads the state of the keyboard

	if(lpdikey) {
		if(lpdikey->GetDeviceState(256, (LPVOID)keyboard_state) != DI_OK)
			return(0);
	} else {
		// keyboard isn't plugged in, zero out state
		memset(keyboard_state, 0, sizeof(keyboard_state));

		// return error
		return(0);
	} // end else

	// return sucess
	return(1);

} // end Input::Read_Keyboard

///////////////////////////////////////////////////////////

void Input::Release_Joystick(void)
{
	// this function unacquires and releases the joystick

	if(lpdijoy) {
		lpdijoy->Unacquire();
		lpdijoy->Release();
	} // end if

} // end Input::Release_Joystick

///////////////////////////////////////////////////////////

void Input::Release_Mouse(void)
{
	// this function unacquires and releases the mouse

	if(lpdimouse) {
		lpdimouse->Unacquire();
		lpdimouse->Release();
	} // end if

} // end Input::Release_Mouse

///////////////////////////////////////////////////////////

void Input::Release_Keyboard(void)
{
	// this function unacquires and releases the keyboard

	if(lpdikey) {
		lpdikey->Unacquire();
		lpdikey->Release();
	} // end if

} // end Input::Release_Keyboard


void Input::SetJoyName(char* name)
{
	strcpy_s(joyname, name);
}


bool Input::IsKeyDown(int key)
{
	if(key < 0 || key >= 256) return false;
	if(keyboard_state[key] != 0) return true;

	return false;

}


softbreeze_namespace_end
