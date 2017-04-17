
#include "..\..\LqnEngine\includes\Game.h"
using namespace std;


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{


	string desc;
	Game game = Game();
	if (!game.Initialize(hInstance)) {
		return 1;
	}

	game.Loop();

	if (!game.Shutdown()) {
		return 1;
	}

	return 0;
}

