#include "..\includes\Game.h"
#define LOGNAME "ErrorLog.txt"
Game::Game() {
}

bool Game::Initialize(HINSTANCE hInstance) {
	static MSG	msg;			// Estructura de mensajes
	static bool	done = false;	// Si debo interrumpir el loop
	int screenWidth = 1280;
	int screenHeight = 768;

	// Registro la clase
	window.registerClass(hInstance);

	if (!LogFile::Initialize(LOGNAME)) {
		LogFile::Write("Can't set up LogFile");
		return false;
	}

	// Creo la Window
	if (!window.createWindow(hInstance,
		L"El mejor titulo",
		screenWidth, screenHeight)) {
		LogFile::Write("Can't create window");
		return false;
	}


	if (!Time::Initialize()) {
		LogFile::Write("Can't initialize timer");
		return false;
	}

	if (!graphics.Initialize(window.getHwnd(), screenWidth, screenHeight)) {
		LogFile::Write("Can't load engine");
		return false;
	}

	if (!textureManager.Create(&graphics)) {
		LogFile::Write("Can't create texture manager");
		return false;
	}
	if (!input.Initialize(hInstance, window.getHwnd(), screenWidth, screenHeight)) {
		LogFile::Write("Can't initialize input");
		return false;
	}
	if(!colManager.Initialize()){
		LogFile::Write("Can't initialize collision manager");
		return false;
	}
	if (!modelImporter.Initialize(&graphics, &textureManager)) {
		LogFile::Write("Can't initialize model Importer");
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
			input.Frame();
			done = !OnUpdate();
			colManager.CheckCollision();
			graphics.Clear();
			graphics.Begin();
			OnDraw();
			graphics.End();
			graphics.Present();
			Time::SetFrameTime();
		}
	}
}
bool Game::Shutdown() {
	graphics.Shutdown();
	input.Shutdown();
	return true;
}

bool Game::OnInit() {
	return true; 
}

void Game::OnDraw() {}

bool Game::OnUpdate() { return true; }

bool Game::OnShutDown() { return true; }