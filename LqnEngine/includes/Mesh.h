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
	vector<VertexUV>* transformedVertex;
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
		transformedVertex = new vector<VertexUV>();
		index = new vector<short>();
		for (size_t i = 0; i < pvertex.size(); i++)
		{
			vertex->push_back(pvertex[i]);
			transformedVertex->push_back(pvertex[i]);
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

	void Update() {
		Entity3D::Update();
	}
	
	void CalculateBounds() {
		//if (gameObject->GetHasChange()) {
			CalculateVertices();
		//}
		SetMaxBounds();
		SetMinBounds();
		gameObject->SetGameObjectMinBounds(minBounds);
		gameObject->SetGameObjectMaxBounds(maxBounds);
	}

	void Draw() {
		Entity3D::graphics->BindTexture(m_texture);
		Entity3D::Draw();

		//VertexBuffer
		vBuffer->Lock(0, 0, (void**)&pVoid,
			0);
		memcpy(pVoid, transformedVertex->data(), sizeof(VertexUV)*transformedVertex->size());
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
		graphics->pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, transformedVertex->size(), 0, index->size() / 3);
		//Si se mueve chequeo maximo y minimo denuevo
		if (debugMode) {
			//This code needs to be updated to the new Matrix system

			//if (boundingBox != NULL)
			//{
			//	graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			//	graphics->PushCurrentlMatrix();
			//	graphics->LoadIdentity();
			//	boundingBox->Draw();
			//	graphics->PopLastMatrix();
			//	graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			//}
			//else {
			//	vector<VertexUV> boundingVertex;
			//	boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, minBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, minBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, minBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, minBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, maxBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, maxBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, maxBounds->z, 0, 0, 0, 0, 0));
			//	boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, maxBounds->z, 0, 0, 0, 0, 0));
			//
			//	vector<short> boundingIndeces;
			//	//Front
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(1);
			//	boundingIndeces.push_back(2);
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(2);
			//	boundingIndeces.push_back(3);
			//	//Back
			//	boundingIndeces.push_back(4);
			//	boundingIndeces.push_back(5);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(4);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(7);
			//	//Left
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(4);
			//	boundingIndeces.push_back(7);
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(7);
			//	boundingIndeces.push_back(3);
			//	//Right
			//	boundingIndeces.push_back(1);
			//	boundingIndeces.push_back(5);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(1);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(2);
			//	//Top
			//	boundingIndeces.push_back(3);
			//	boundingIndeces.push_back(2);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(3);
			//	boundingIndeces.push_back(6);
			//	boundingIndeces.push_back(7);
			//	//Down
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(1);
			//	boundingIndeces.push_back(5);
			//	boundingIndeces.push_back(0);
			//	boundingIndeces.push_back(5);
			//	boundingIndeces.push_back(4);
			//
			//	boundingBox = new Mesh(graphics, textureManager, boundingVertex, boundingIndeces);
			//	graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			//	graphics->PushCurrentlMatrix();
			//	graphics->LoadIdentity();
			//	boundingBox->Draw();
			//	graphics->PopLastMatrix();
			//	graphics->pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			//}
		}

	}

	void SetTexture(LPCWSTR texturePath) {
		m_texture = textureManager->LoadTexture(texturePath);
	}

	void SetTexture(Texture* texture) {
		m_texture = texture;
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

	virtual void SetParent(NodeWithChildren * rparent) {
		Entity3D::SetParent(rparent);
		//SetMaxBounds();
		//SetMinBounds();
		//gameObject->SetGameObjectMinBounds(minBounds);
		//gameObject->SetGameObjectMaxBounds(maxBounds);
	}


private:

	void CalculateVertices() {
		D3DXVECTOR4 transformedVertexVector;
		D3DXVECTOR3 originalVertexVector;
		D3DXMATRIX * worldMatrix = gameObject->GetWorldMatrix();
		for (size_t i = 0; i < vertex->size(); i++)
		{
			originalVertexVector.x = vertex->at(i).x;
			originalVertexVector.y = vertex->at(i).y;
			originalVertexVector.z = vertex->at(i).z;
			D3DXVec3Transform(&transformedVertexVector, &originalVertexVector, worldMatrix);
			transformedVertex->at(i).x = transformedVertexVector.x;
			transformedVertex->at(i).y = transformedVertexVector.y;
			transformedVertex->at(i).z = transformedVertexVector.z;
		}
	}

	void SetMaxBounds() {
		float x, y, z;

		for (size_t i = 0; i < transformedVertex->size(); i++)
		{
			if (i == 0)
			{
				x = transformedVertex->at(i).x;
				y = transformedVertex->at(i).y;
				z = transformedVertex->at(i).z;
			}
			else
			{
				if (x < transformedVertex->at(i).x) {
					x = transformedVertex->at(i).x;
				}
				if (y < transformedVertex->at(i).y) {
					y = transformedVertex->at(i).y;
				}
				if (z < transformedVertex->at(i).z) {
					z = transformedVertex->at(i).z;
				}
			}
		}
		maxBounds = new D3DXVECTOR3(x, y, z);
	}

	void SetMinBounds() {
		float x, y, z;

		for (size_t i = 0; i < transformedVertex->size(); i++)
		{
			if (i == 0)
			{
				x = transformedVertex->at(i).x;
				y = transformedVertex->at(i).y;
				z = transformedVertex->at(i).z;
			}
			else
			{
				if (x > transformedVertex->at(i).x) {
					x = transformedVertex->at(i).x;
				}
				if (y > transformedVertex->at(i).y) {
					y = transformedVertex->at(i).y;
				}
				if (z > transformedVertex->at(i).z) {
					z = transformedVertex->at(i).z;
				}
			}
		}
		minBounds = new D3DXVECTOR3(x, y, z);
	}

};



#endif