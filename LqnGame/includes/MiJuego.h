#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	Quad* cuadradito;
	Sprite* sprite;
	Quad* cuadradito2;
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};