
#include <time.h>

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <softbreeze/softbreeze.h>
#include <softbreeze/core/graphic.h>

#include "game.h"


Game::Game()
{
}

Game::~Game()
{
}


int Game::Init(HWND hWnd)
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();
	HRESULT result = graphic.Init(hWnd);

	srand(time(nullptr));

	return result;
}

void Game::Shutdown()
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();
	graphic.Cleanup();

}

void Game::Main()
{
	breeze::Graphic& graphic = breeze::Graphic::Instance();


	breeze::uint32 x = rand()%graphic.GetWidth();
	breeze::uint32 y = rand()%graphic.GetHeight();

	graphic.SetPixel(x, y, 0xFFFFFFFF);
	graphic.Render();
}

