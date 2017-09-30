#include "..\..\LqnEngine\includes\Game.h"

class MiJuego :public Game {
	//Sprite* sprite;
	//Sprite* sprite2;
	//Mesh* mesh;
	//Quad* quad;
	//TileMap* tilemap;
	//TileMap* tilemap2;
	//Vertex *vertex;
	//short * index;
	Scene * scene;
	GameObject * goQuad;
	Camera* camera;
	GameObject * goCamera;
	Mesh * mesh;
	GameObject * goMesh;

	bool movingRight;
	int mouseX;
	int mouseY;
	int lastMouseX;
	int lastMouseY;
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
};