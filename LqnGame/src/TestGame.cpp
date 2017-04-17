// ---------------------------------------------------------------------
// Archivo: main.cpp
// Desc: Ejemplo de creaci�n de Windows
//
// Autor: Juan Pablo (McKrackeN) Bettini
// ---------------------------------------------------------------------
#include "..\..\LqnEngine\includes\Game.h"
using namespace std;

// ---------------------------------------------------------------------
// WinMain
// Es el equivalente a la cl�sica funci�n int main ();
// ---------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{


	hInstance = hPrevInstance;
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

