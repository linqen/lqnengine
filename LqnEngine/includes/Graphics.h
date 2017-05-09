#ifndef GRAPHICS_H
#define GRAPHICS_H
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "ImportExport.h"
//#include "Vertex.h"
#include "VertexUV.h"

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")

class LQN_API Graphics {
public:
	LPDIRECT3D9 pD3D; // the Direct3d object
	LPDIRECT3DDEVICE9 pd3dDevice; // the Direct3d Device
	D3DVIEWPORT9 viewport;
	IDirect3DVertexBuffer9* vBuffer = 0;
	IDirect3DTexture9* m_texture = 0;

	bool Initialize(HWND wndHandle);
	bool SetupScene();
	void Shutdown();
	void Clear();
	void Begin();
	void End();
	void Present();
};

#endif