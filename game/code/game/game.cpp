
#include <time.h>

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <softbreeze/softbreeze.h>
#include <softbreeze/math/vector2.h>
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

	graphic.ClearCanvas(0x00000000);

	breeze::uint32 beginX = rand()%graphic.GetWidth();
	breeze::uint32 beginY = rand()%graphic.GetHeight();

	breeze::uint32 endX = rand()%graphic.GetWidth();
	breeze::uint32 endY = rand()%graphic.GetHeight();

	breeze::Vector2 begin(beginX, beginY);
	breeze::Vector2 end(endX, endY);
	graphic.DrawLine(begin, end, 0xFFFFFFFF);


	graphic.Render();
}

