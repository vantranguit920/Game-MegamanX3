#include <windows.h>
#include "Game.h"
using namespace Define;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game(hInstance, WinWidth, WinHeight, "Mega Man X3", 60);

	game.Init();
	game.Run();

	return 0;
}


