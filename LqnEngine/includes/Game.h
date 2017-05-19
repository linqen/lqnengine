#ifndef GAME_H
#define GAME_H
using namespace std;
#include "Window.h"
#include "Graphics.h"
#include "ImportExport.h"
#include "Quad.h"

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
	Window window;
};


#endif