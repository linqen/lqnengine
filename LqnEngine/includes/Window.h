#ifndef WINDOW_H
#define WINDOW_H
using namespace std;
#include <windows.h>
#include <string>
#include "ImportExport.h"

class LQN_API Window {
private:
	HWND hWnd;
	wstring		className;
public:
	bool createWindow(HINSTANCE hInstance, wstring title, int width, int height);
	void registerClass(HINSTANCE hInstance);
	Window();
	HWND getHwnd();
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


#endif