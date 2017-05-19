#ifndef GRAPHICS_H
#define GRAPHICS_H
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "ImportExport.h"
#include "Vertex.h"
#include "VertexUV.h"
#include "VertexBufferManager.h"

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")

class LQN_API Graphics {
public:
	LPDIRECT3D9 pD3D; // the Direct3d object
	LPDIRECT3DDEVICE9 pd3dDevice; // the Direct3d Device
	D3DVIEWPORT9 viewport;
	VertexBufferManager<Vertex,Vertex::fvf> vertexManager;
	D3DXMATRIX d3dmat;
	//IDirect3DVertexBuffer9* vBuffer = 0;
	IDirect3DTexture9* m_texture = 0;

	bool Initialize(HWND wndHandle);
	bool SetupScene();
	void Shutdown();
	void Clear();
	void Begin();
	void End();
	void Present();
	void LoadIdentity();
	void Translate(float xPos,float yPos,float zPos);
	void RotateZ(float zRot);
	void Scale(float xScale, float yScale, float zScale);
	void Draw2D(Vertex* vertex, _D3DPRIMITIVETYPE primitive,float vertexCount);
};

#endif