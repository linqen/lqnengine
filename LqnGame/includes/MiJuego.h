#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	Sprite* sprite;
	Sprite* sprite2;
	Quad* quad;
	Time time;
	bool movingRight;
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};