// T3DLIB2.H - Header file for T3DLIB2.CPP game engine library

// watch for multiple inclusions
#ifndef SOFTBREEZE_INPUT
#define SOFTBREEZE_INPUT


softbreeze_namespace_beg


class Input
{
public:
	Input();
	~Input();

	static	Input& Instance();

// input
	int			Init(HINSTANCE instance);
	void		Shutdown(void);

	int			Init_Joystick(HWND hWnd, int min_x=-256, int max_x=256, int min_y=-256, int max_y=256, int dead_band = 10);
	int			Init_Mouse(HWND hWnd);
	int			Init_Keyboard(HWND hWnd);

	int			Read_Joystick(void);
	int			Read_Mouse(void);
	int			Read_Keyboard(void);

	void		Release_Joystick(void);
	void		Release_Mouse(void);
	void		Release_Keyboard(void);

	void		SetJoyName(char* name);
	bool		IsKeyDown(int key);

private:

	static Input*			_inst;

	// directinput globals
	LPDIRECTINPUT8			lpdi;         // dinput object
	LPDIRECTINPUTDEVICE8	lpdikey;      // dinput keyboard
	LPDIRECTINPUTDEVICE8	lpdimouse;    // dinput mouse
	LPDIRECTINPUTDEVICE8	lpdijoy;      // dinput joystick 
	GUID					joystickGUID; // guid for main joystick
	char					joyname[80];  // name of joystick

	// these contain the target records for all di input packets
	UCHAR					keyboard_state[256]; // contains keyboard state table
	DIMOUSESTATE			mouse_state;  // contains state of mouse
	DIJOYSTATE				joy_state;      // contains state of joystick
	int						joystick_found;        // tracks if stick is plugged in


};



softbreeze_namespace_end

#endif