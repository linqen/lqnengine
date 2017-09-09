#ifndef MESH_H
#define MESH_H
using namespace std;

#include "VertexUV.h"
#include "Entity3D.h"
#include "TextureManager.h"
#include "ObjImporter.h"
#include <vector>

class LQN_API Mesh : public Entity3D {
	vector<VertexUV>* vertex;
	vector<short>* index;
	IDirect3DVertexBuffer9* vBuffer;
	IDirect3DIndexBuffer9* iBuffer;
	Texture* m_texture;
	TextureManager* textureManager;
	VOID* pVoid;
	VOID* piVoid;
public:
	Mesh(Graphics *graphics, TextureManager* ptextureManager, vector<VertexUV> pvertex, vector<short> pindex) : Entity3D(graphics) {
		textureManager = ptextureManager;
		m_texture = NULL;
		vertex = new vector<VertexUV>();
		index = new vector<short>();
		for (size_t i = 0; i < pvertex.size(); i++)
		{vertex->push_back(pvertex[i]);}

		for (size_t i = 0; i < pindex.size(); i++)
		{index->push_back(pindex[i]);}

		//VertexBuffer
		graphics->pd3dDevice->CreateVertexBuffer(vertex->size() * sizeof(VertexUV),
			0,
			VertexUV::fvf,
			D3DPOOL_MANAGED,
			&vBuffer,
			NULL);

		//IndexBuffer
		graphics->pd3dDevice->CreateIndexBuffer(index->size() * sizeof(short),
			0,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&iBuffer,
			NULL);

	}
	Mesh(Graphics *graphics, TextureManager* ptextureManager, const char * path) : Entity3D(graphics) {
		textureManager = ptextureManager;
		m_texture = NULL;
		vertex = new vector<VertexUV>();
		index = new vector<short>();

		ObjImporter::LoadOBJ(path, &vertex, &index);

		//VertexBuffer
		graphics->pd3dDevice->CreateVertexBuffer(vertex->size() * sizeof(VertexUV),
			0,
			VertexUV::fvf,
			D3DPOOL_MANAGED,
			&vBuffer,
			NULL);

		//IndexBuffer
		graphics->pd3dDevice->CreateIndexBuffer(index->size() * sizeof(short),
			0,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&iBuffer,
			NULL);

	}

	void Draw() {
		Entity3D::graphics->BindTexture(m_texture);
		Entity3D::Draw();

		//VertexBuffer
		vBuffer->Lock(0, 0, (void**)&pVoid,
			0);
		memcpy(pVoid, vertex->data(), sizeof(VertexUV)*vertex->size());
		vBuffer->Unlock();

		//IndexBuffer
		iBuffer->Lock(0, 0, (void**)&pVoid,
			0);
		memcpy(pVoid, index->data(), sizeof(short)*index->size());
		iBuffer->Unlock();
		
		//Device Setting
		graphics->pd3dDevice->SetFVF(VertexUV::fvf);
		graphics->pd3dDevice->SetVertexShader(NULL);
		graphics->pd3dDevice->SetStreamSource(0, vBuffer, 0, sizeof(VertexUV));
		graphics->pd3dDevice->SetIndices(iBuffer);
		graphics->pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertex->size(), 0, index->size() / 3);
	}

	void SetTexture(LPCWSTR texturePath) {
		m_texture = textureManager->LoadTexture(texturePath);
	}
};



#endif