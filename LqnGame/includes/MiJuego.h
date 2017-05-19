#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	Quad* cuadradito;
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};