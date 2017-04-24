#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};