

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include <softbreeze/softbreeze.h>
#include <softbreeze/core/graphic_new.h>

#include "game.h"


Game::Game()
{
}

Game::~Game()
{
}


int Game::Init(HWND hWnd)
{
	softbreeze::Graphic& graphic = softbreeze::Graphic::Instance();
	HRESULT result = graphic.Init(hWnd);

	return result;
}

void Game::Shutdown()
{
	softbreeze::Graphic& graphic = softbreeze::Graphic::Instance();
	graphic.Cleanup();

}

void Game::Main()
{
	softbreeze::Graphic& graphic = softbreeze::Graphic::Instance();
	graphic.Render();
}

