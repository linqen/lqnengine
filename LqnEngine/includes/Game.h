#ifndef GAME_H
#define GAME_H
using namespace std;
#include "Window.h"
#include "Graphics.h"
#include "ImportExport.h"

class LQN_API Game {
public:
	Game();
	bool Initialize(HINSTANCE hInstance);
	void Loop();
	bool Shutdown();
protected:
	bool OnInit();
	bool OnUpdate();
	void OnDraw();
	bool OnShutDown();
	Graphics graphics;
	Window window;
};


#endif