#ifndef MESH_H
#define MESH_H
using namespace std;

#include "Vertex.h"
#include "Entity3D.h"
#include "TextureManager.h"
#include <vector>

class LQN_API Mesh : public Entity3D {
	vector<Vertex> vertex;
	vector<short> index;
	IDirect3DVertexBuffer9* vBuffer;
	IDirect3DIndexBuffer9* iBuffer;
	//Texture* m_texture;
	TextureManager* textureManager;
	int vertexCount;
	int indexCount;
	VOID* pVoid;
	VOID* piVoid;
public:
	Mesh(Graphics *graphics, TextureManager* textureManager, vector<Vertex> pvertex, vector<short> pindex, int mvertexCount, int mindexCount) : Entity3D(graphics) {
		vertexCount = mvertexCount;
		indexCount = mindexCount;

		for (size_t i = 0; i < vertexCount; i++)
		{
			vertex.push_back(pvertex[i]);
		}

		for (size_t i = 0; i < indexCount; i++)
		{
			index.push_back(pindex[i]);
		}
		//m_texture = textureManager->LoadTexture(L"tileset.png");
		graphics->pd3dDevice->CreateVertexBuffer(vertexCount * sizeof(Vertex),
			0,
			Vertex::fvf,
			D3DPOOL_MANAGED,
			&vBuffer,
			NULL);

		//Index
		graphics->pd3dDevice->CreateIndexBuffer(indexCount * sizeof(short),
			0,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&iBuffer,
			NULL);

	}

	void Draw() {
		Entity3D::graphics->BindTexture(NULL);
		Entity3D::Draw();
		vBuffer->Lock(0, 0, (void**)&pVoid,
			0);
		memcpy(pVoid, vertex.data(), sizeof(Vertex)*vertex.size());

		vBuffer->Unlock();

		iBuffer->Lock(0, 0, (void**)&pVoid,
			0);

		memcpy(pVoid, index.data(), sizeof(short)*vertex.size());

		iBuffer->Unlock();

		graphics->pd3dDevice->SetFVF(Vertex::fvf);
		graphics->pd3dDevice->SetVertexShader(NULL);
		graphics->pd3dDevice->SetStreamSource(0, vBuffer, 0, sizeof(Vertex));
		graphics->pd3dDevice->SetIndices(iBuffer);

		HRESULT hRes = graphics->pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, indexCount / 3);

	}

	void SetTexture(LPCWSTR texturePath) {
		//m_texture = textureManager->LoadTexture(texturePath);
	}
};



#endif