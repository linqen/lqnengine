#include "..\includes\Game.h"

Game::Game() {
}

bool Game::Initialize(HINSTANCE hInstance) {
	static MSG	msg;			// Estructura de mensajes
	static bool	done = false;	// Si debo interrumpir el loop
	
	window = Window();
	//graphics = Graphics();
	// Registro la clase
	window.registerClass(hInstance);

	// Creo la Window
	if (!window.createWindow(hInstance,
		L"El mejor titulo",
		800, 600)) {
		return false;
	}

	if (!graphics.Initialize(window.getHwnd())) {
		return false;
	}

	if (!textureManager.Create(&graphics)) {
		return false;
	}
	if (!time.Initialize()) {
		return false;
	}

	OnInit();
	return true;
}

void Game::Loop() {
	static MSG	msg;			// Estructura de mensajes
	static bool	done = false;	// Si debo interrumpir el loop
								// Loop principal
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				done = true;			// ALT-F4
		}
		else
		{
			OnUpdate();
			graphics.Clear();
			graphics.Begin();
			OnDraw();
			graphics.End();
			graphics.Present();
			time.SetFrameTime();
		}
	}
}
bool Game::Shutdown() {
	graphics.Shutdown();
	return true;
}

bool Game::OnInit() {
	return true; 
}

void Game::OnDraw() {}

bool Game::OnUpdate() { return true; }

bool Game::OnShutDown() { return true; }