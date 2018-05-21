#ifndef GRAPHICS_H
#define GRAPHICS_H
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>
#include <D3D9Types.h>
#include <Windows.h>
#include "ImportExport.h"
#include "Vertex.h"
#include "VertexUV.h"
#include "VertexBufferManager.h"
#include "Texture.h"
#include "LogFile.h"
#include <vector>

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")

class LQN_API Graphics {
public:
	LPDIRECT3D9 pD3D; // the Direct3d object
	LPDIRECT3DDEVICE9 pd3dDevice; // the Direct3d Device
	D3DVIEWPORT9 viewport;
	VertexBufferManager<Vertex, Vertex::fvf> vertexManager;
	VertexBufferManager<VertexUV, VertexUV::fvf> textureVertexManager;
	Texture* lastTexture;
	D3DXMATRIX d3dmat;
	D3DLIGHT9 d3dLight;

	bool Initialize(HWND wndHandle, int screenWidth, int screenHeight);
	bool SetupScene();
	void Shutdown();
	void Clear();
	void Begin();
	void End();
	void Present();
	void Draw2D(Vertex* vertex, _D3DPRIMITIVETYPE primitive, float vertexCount);
	void Draw3D(VertexUV* vertex, int* index, int vertexCount, int indexCount, _D3DPRIMITIVETYPE primitive);
	void DrawSprite(VertexUV* vertexUV, _D3DPRIMITIVETYPE primitive, float vertexCount);
	IDirect3DTexture9* LoadTexture(LPCWSTR texturePath);
	void BindTexture(Texture* textureToBind);
	void ReleaseTexture(Texture* textureToUnload);
	void SetViewTransform(D3DXMATRIX * viewTransform);
	void SetProjectionMatrix(D3DXMATRIX * projectionMatrix);
};

#endif