#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	Sprite* sprite;
	Sprite* sprite2;
	Quad* quad;
	TileMap* tilemap;
	TileMap* tilemap2;
	bool movingRight;
	int mouseX;
	int mouseY;
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};