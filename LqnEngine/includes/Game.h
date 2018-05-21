#ifndef GAME_H
#define GAME_H
using namespace std;
#include "Window.h"
#include "Graphics.h"
#include "Camera.h"
#include "ImportExport.h"
#include "Quad.h"
#include "Mesh.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TextureManager.h"
#include "Time.h"
#include "Input.h"
#include "CollisionManager.h"
#include "LogFile.h"
#include "GameObject.h"
#include "Component.h"
#include "CameraMovement.h"
#include "ModelImporter.h"
class LQN_API Game {
public:
	Game();
	bool Initialize(HINSTANCE hInstance);
	void Loop();
	bool Shutdown();
protected:
	virtual bool OnInit();
	virtual bool OnUpdate();
	virtual void OnDraw();
	virtual bool OnShutDown();
	Graphics graphics;
	TextureManager textureManager;
	Window window;
	Input input;
	CollisionManager colManager;
	ModelImporter modelImporter;
};
#endif