#ifndef INPUT_H
#define INPUT_H
#include "ImportExport.h"
#include <windows.h>
#include <dinput.h>
#include "KeyCode.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
class LQN_API Input {
public:
	Input();

	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame();

	bool GetKey(KeyCode key);
	void GetMouseLocation(int& mouseX, int& mouseY);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};
#endif