#ifndef GRAPHICS_H
#define GRAPHICS_H
using namespace std;

#include <d3d9.h>
#include <Windows.h>
#include "ImportExport.h"
class LQN_API Graphics {
public:
	LPDIRECT3D9 pD3D; // the Direct3d object
	LPDIRECT3DDEVICE9 pd3dDevice; // the Direct3d Device

	bool Initialize(HWND wndHandle);
	void Shutdown();
	void Clear();
	void Begin();
	void End();
	void Present();
};

#endif