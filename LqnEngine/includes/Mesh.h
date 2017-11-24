#ifndef MESH_H
#define MESH_H
using namespace std;

#include "VertexUV.h"
#include "Vertex.h"
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
	Mesh* boundingBox = NULL;
	TextureManager* textureManager;
	VOID* pVoid;
	VOID* piVoid;
	D3DXVECTOR3 * minBounds = NULL;
	D3DXVECTOR3 * maxBounds = NULL;
	bool debugMode = false;
public:
	Mesh(Graphics *graphics, TextureManager* ptextureManager, vector<VertexUV> pvertex, vector<short> pindex) : Entity3D(graphics) {
		textureManager = ptextureManager;
		m_texture = NULL;
		vertex = new vector<VertexUV>();
		index = new vector<short>();
		for (size_t i = 0; i < pvertex.size(); i++)
		{
			vertex->push_back(pvertex[i]);
		}

		for (size_t i = 0; i < pindex.size(); i++)
		{
			index->push_back(pindex[i]);
		}

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

	void Update() {
		if (gameObject->GetHasChange()) {
			SetMaxBounds();
			SetMinBounds();
			gameObject->SetGameObjectMinBounds(minBounds);
			gameObject->SetGameObjectMaxBounds(maxBounds);
		}
		Entity3D::Update();
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
		//Si se mueve chequeo maximo y minimo denuevo
		if (debugMode) {
			if (boundingBox != NULL)
			{
				graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				graphics->PushCurrentlMatrix();
				graphics->LoadIdentity();
				boundingBox->Draw();
				graphics->PopLastMatrix();
				graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
			else {
				vector<VertexUV> boundingVertex;
				boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, minBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, minBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, minBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, minBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, maxBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, maxBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, maxBounds->z, 0, 0));
				boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, maxBounds->z, 0, 0));

				vector<short> boundingIndeces;
				//Front
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(1);
				boundingIndeces.push_back(2);
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(2);
				boundingIndeces.push_back(3);
				//Back
				boundingIndeces.push_back(4);
				boundingIndeces.push_back(5);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(4);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(7);
				//Left
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(4);
				boundingIndeces.push_back(7);
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(7);
				boundingIndeces.push_back(3);
				//Right
				boundingIndeces.push_back(1);
				boundingIndeces.push_back(5);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(1);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(2);
				//Top
				boundingIndeces.push_back(3);
				boundingIndeces.push_back(2);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(3);
				boundingIndeces.push_back(6);
				boundingIndeces.push_back(7);
				//Down
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(1);
				boundingIndeces.push_back(5);
				boundingIndeces.push_back(0);
				boundingIndeces.push_back(5);
				boundingIndeces.push_back(4);

				boundingBox = new Mesh(graphics, textureManager, boundingVertex, boundingIndeces);
				graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				graphics->PushCurrentlMatrix();
				graphics->LoadIdentity();
				boundingBox->Draw();
				graphics->PopLastMatrix();
				graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
		}

	}

	void SetTexture(LPCWSTR texturePath) {
		m_texture = textureManager->LoadTexture(texturePath);
	}

	void SetDebugMode(bool status) {
		debugMode = status;
	}

	D3DXVECTOR3 GetMinBounds() {
		if (minBounds == NULL) {
			SetMinBounds();
		}
		return D3DXVECTOR3(minBounds->x, minBounds->y, minBounds->z);
	}

	D3DXVECTOR3 GetMaxBounds() {
		if (maxBounds == NULL) {
			SetMaxBounds();
		}
		return D3DXVECTOR3(maxBounds->x, maxBounds->y, maxBounds->z);
	}

	virtual void SetParent(Node * rparent) {
		Entity3D::SetParent(rparent);
		SetMaxBounds();
		SetMinBounds();
		gameObject->SetGameObjectMinBounds(minBounds);
		gameObject->SetGameObjectMaxBounds(maxBounds);
	}


private:
	void SetMaxBounds() {
		float x, y, z;
		D3DXVECTOR4 transformedVertex;
		D3DXVECTOR3 actualVertex;

		graphics->PushCurrentlMatrix();
		graphics->Translate(gameObject->xPos, gameObject->yPos, gameObject->zPos);
		graphics->RotateX(gameObject->xRot);
		graphics->RotateY(gameObject->yRot);
		graphics->RotateZ(gameObject->zRot);
		graphics->Scale(gameObject->xScale, gameObject->yScale, gameObject->zScale);
		for (size_t i = 0; i < vertex->size(); i++)
		{
			actualVertex.x = vertex->at(i).x;
			actualVertex.y = vertex->at(i).y;
			actualVertex.z = vertex->at(i).z;

			D3DXVec3Transform(&transformedVertex, &actualVertex, &graphics->d3dmat);

			if (i == 0)
			{
				x = transformedVertex.x;
				y = transformedVertex.y;
				z = transformedVertex.z;
			}
			else
			{
				if (x < transformedVertex.x) {
					x = transformedVertex.x;
				}
				if (y < transformedVertex.y) {
					y = transformedVertex.y;
				}
				if (z < transformedVertex.z) {
					z = transformedVertex.z;
				}
			}
		}
		maxBounds = new D3DXVECTOR3(x, y, z);
		graphics->PopLastMatrix();
	}

	void SetMinBounds() {
		float x, y, z;

		D3DXVECTOR4 transformedVertex;
		D3DXVECTOR3 actualVertex;

		graphics->PushCurrentlMatrix();
		graphics->Translate(gameObject->xPos, gameObject->yPos, gameObject->zPos);
		graphics->RotateX(gameObject->xRot);
		graphics->RotateY(gameObject->yRot);
		graphics->RotateZ(gameObject->zRot);
		graphics->Scale(gameObject->xScale, gameObject->yScale, gameObject->zScale);
		for (size_t i = 0; i < vertex->size(); i++)
		{
			actualVertex.x = vertex->at(i).x;
			actualVertex.y = vertex->at(i).y;
			actualVertex.z = vertex->at(i).z;

			D3DXVec3Transform(&transformedVertex, &actualVertex, &graphics->d3dmat);

			if (i == 0)
			{
				x = transformedVertex.x;
				y = transformedVertex.y;
				z = transformedVertex.z;
			}
			else
			{
				if (x > transformedVertex.x) {
					x = transformedVertex.x;
				}
				if (y > transformedVertex.y) {
					y = transformedVertex.y;
				}
				if (z > transformedVertex.z) {
					z = transformedVertex.z;
				}
			}
		}
		minBounds = new D3DXVECTOR3(x, y, z);
		graphics->PopLastMatrix();
	}

};



#endif