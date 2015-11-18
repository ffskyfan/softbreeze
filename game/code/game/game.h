

#ifndef SOFTBREEZE_GAME_H
#define SOFTBREEZE_GAME_H


class Game
{
public:
	Game();
	~Game();

	int		Init(HINSTANCE instance, HWND hWnd);
	void	Shutdown();
	void	Main();
};








#endif