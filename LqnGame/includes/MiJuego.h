#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	GameObject * goSprite;
	Sprite* sprite;
	GameObject * goSprite2;
	Sprite* sprite2;
	GameObject * goQuad2;
	Quad* quad2;
	GameObject * goTileMap;
	TileMap* tilemap;
	GameObject * goTileMap2;
	TileMap* tilemap2;
	Vertex *vertex;
	short * index;
	Scene * scene;
	GameObject * goQuad;
	Camera* camera;
	CameraMovement * cameraMov;
	GameObject * goCamera;
	Mesh * mesh;
	GameObject * goMesh;

protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};