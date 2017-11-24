#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ImportExport.h"
#include "NodeWithChildren.h"
class LQN_API GameObject : public NodeWithChildren {
public:
	GameObject(Graphics * graphics) :NodeWithChildren(graphics) {
		SetGameObjectMinBounds(new D3DXVECTOR3(this->xPos, this->yPos, this->zPos));
		SetGameObjectMaxBounds(new D3DXVECTOR3(this->xPos, this->yPos, this->zPos));
		globalMaxBounds = GetGlobalMaxBounds();
		globalMinBounds = GetGlobalMinBounds();
		SetGlobalVerticesWithBounds();
	};

	virtual void Update() {


		if (xPos != lastXPos || yPos != lastYPos || zPos != lastZPos ||
			xRot != lastXRot || yRot != lastYRot || zRot != lastZRot ||
			xScale != lastXScale || yScale != lastYScale || zScale != lastZScale)
		{
			hasChange = true;
		}

		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update();
		}
		//Check again because components maybe change something
		if (xPos != lastXPos ||	yPos != lastYPos ||	zPos != lastZPos ||
			xRot != lastXRot ||	yRot != lastYRot ||	zRot != lastZRot ||
			xScale != lastXScale ||	yScale != lastYScale ||	zScale != lastZScale)
		{
			hasChange = true;
		}
		if (hasChange && !hasSettedBounds) {
			personalMinBounds->x = xPos;
			personalMinBounds->y = yPos;
			personalMinBounds->z = zPos;
			personalMaxBounds->x = xPos;
			personalMaxBounds->y = yPos;
			personalMaxBounds->z = zPos;
			hasSettedBounds = true;
		}
		if (hasSettedBounds) {
			SetVerticesWithBounds();
			globalMaxBounds = GetGlobalMaxBounds();
			globalMinBounds = GetGlobalMinBounds();
			SetGlobalVerticesWithBounds();
		}
		lastXPos = xPos;
		lastYPos = yPos;
		lastZPos = zPos;
		lastXRot = xRot;
		lastYRot = yRot;
		lastZRot = zRot;
		lastXScale = xScale;
		lastYScale = yScale;
		lastZScale = zScale;

		NodeWithChildren::Update();
	}

	virtual void Draw(D3DXPLANE* frustumPlane, D3DXVECTOR3* minFrustumBoxBounds, D3DXVECTOR3* maxFrustumBoxBounds) {

		for (size_t i = 0; i < childrens.size(); i++)
		{
			//Check if !hasChange because if hasChange i already calculate Global on Update
			if(((GameObject*)childrens[i])->GetHasChange() && !hasChange){
				globalMaxBounds = GetGlobalMaxBounds();
				globalMinBounds = GetGlobalMinBounds();
				SetGlobalVerticesWithBounds();
			}
		}

		if (CheckIsInFrustumBox(minFrustumBoxBounds, maxFrustumBoxBounds, globalMinBounds, globalMaxBounds)
			& CheckIsInFrustum(frustumPlane,globalVertices,1)) {
			graphics->PushCurrentlMatrix();
			graphics->Translate(xPos, yPos, zPos);
			graphics->RotateX(xRot);
			graphics->RotateY(yRot);
			graphics->RotateZ(zRot);
			graphics->Scale(xScale, yScale, zScale);
			if (GetGameObjectMinBounds()!=NULL && GetGameObjectMaxBounds() !=NULL &&
				CheckIsInFrustumBox(minFrustumBoxBounds, maxFrustumBoxBounds, GetGameObjectMinBounds(), GetGameObjectMaxBounds())
				& CheckIsInFrustum(frustumPlane,vertices,2)) {
				for (size_t i = 0; i < components.size(); i++)
				{
					components[i]->Draw();
				}
			}
			NodeWithChildren::Draw(frustumPlane, minFrustumBoxBounds, maxFrustumBoxBounds);

			graphics->PopLastMatrix();
		}
			hasChange = false;
			hasSettedBounds = false;
	}

	bool CheckIsInFrustumBox(D3DXVECTOR3 * frustumBoxMinBounds, D3DXVECTOR3 * frustumBoxMaxBounds, D3DXVECTOR3 * minBounds, D3DXVECTOR3 * maxBounds) {

		bool a, b, c;

		a = (frustumBoxMinBounds->x<=maxBounds->x && frustumBoxMaxBounds->x >= minBounds->x);
		b = (frustumBoxMinBounds->y <= maxBounds->y && frustumBoxMaxBounds->y >= minBounds->y);
		c = (frustumBoxMinBounds->z <= maxBounds->z && frustumBoxMaxBounds->z >= minBounds->z);
		if (a&&b&&c) {
			return true;
		}
		//float dX, dY, dZ;
		//dX = abs((frustumBoxMaxBounds->x + frustumBoxMinBounds->x) / 2 - (maxBounds->x + minBounds->x) / 2);
		//dY = abs((frustumBoxMaxBounds->y + frustumBoxMinBounds->y) / 2 - (maxBounds->y + minBounds->y) / 2);
		//dZ = abs((frustumBoxMaxBounds->z + frustumBoxMinBounds->z) / 2 - (maxBounds->z + minBounds->z) / 2);
		//
		//float frustumWidth, objectWidth, frustumHeight, objectHeight, frustumDepth, objectDepth;
		//frustumWidth = abs(frustumBoxMaxBounds->x - frustumBoxMinBounds->x);
		//objectWidth = abs(maxBounds->x - minBounds->x);
		//frustumHeight = abs(frustumBoxMaxBounds->y - frustumBoxMinBounds->y);
		//objectHeight = abs(maxBounds->y - minBounds->y);
		//frustumDepth = abs(frustumBoxMaxBounds->z - frustumBoxMinBounds->z);
		//objectDepth = abs(maxBounds->z - minBounds->z);
		//
		//if (dX < (frustumWidth + objectWidth) / 2 &&
		//	dY < (frustumHeight + objectHeight) / 2 &&
		//	dZ < (frustumDepth + objectDepth) / 2) {
		//
		//	//wstring fileName = name;
		//	//LPCWSTR fullPath = fileName.c_str();
		//	//OutputDebugString(fullPath);
		//	return true;
		//}			
		wstring fileName(L"Ocultando en Box\n");
		LPCWSTR fullPath = fileName.c_str();
		OutputDebugString(fullPath);
		return false;
	}

	bool CheckIsInFrustum(D3DXPLANE* frustumPlane, vector<D3DXVECTOR3*> m_vertices,int debugValue) {
		for (size_t i = 0; i < 6; i++)
		{
			int vertexOut = 0;
			for (size_t j = 0; j < m_vertices.size(); j++)
			{
				if (D3DXPlaneDotCoord(&frustumPlane[i], m_vertices[j]) < 0.0f) {
					vertexOut++;
				}
			}
			if (vertexOut == m_vertices.size()) {
				wstring fileName(L"Ocultando en Frustum\n"+to_wstring(debugValue));
				LPCWSTR fullPath = fileName.c_str();
				OutputDebugString(fullPath);
				return false;
			}
		}
		return true;
	}

	void AddComponent(Node* newComponent) {
		newComponent->SetParent(this);
		components.push_back(newComponent);
	}

	bool RemoveComponent(Node* componentToRemove) { return true; }

	void SetGameObjectMinBounds(D3DXVECTOR3* gameObjectMinBounds) {
		if (personalMinBounds == NULL) {
			personalMinBounds = new D3DXVECTOR3(gameObjectMinBounds->x,
				gameObjectMinBounds->y,
				gameObjectMinBounds->z);
		}
		else {
			personalMinBounds->x = gameObjectMinBounds->x;
			personalMinBounds->y = gameObjectMinBounds->y;
			personalMinBounds->z = gameObjectMinBounds->z;
		}
		hasSettedBounds = true;
	}

	void SetGameObjectMaxBounds(D3DXVECTOR3* gameObjectMaxBounds) {
		if (personalMaxBounds == NULL) {
			personalMaxBounds = new D3DXVECTOR3(gameObjectMaxBounds->x,
				gameObjectMaxBounds->y,
				gameObjectMaxBounds->z);
		}
		else {
			personalMaxBounds->x = gameObjectMaxBounds->x;
			personalMaxBounds->y = gameObjectMaxBounds->y;
			personalMaxBounds->z = gameObjectMaxBounds->z;
		}
		hasSettedBounds = true;
	}

	D3DXVECTOR3* GetGlobalMaxBounds() {
		float x = 0;
		float y = 0;
		float z = 0;
		D3DXVECTOR3* thisGameObjectMaxBounds = GetGameObjectMaxBounds();
		if (thisGameObjectMaxBounds != NULL) {
			x = thisGameObjectMaxBounds->x;
			y = thisGameObjectMaxBounds->y;
			z = thisGameObjectMaxBounds->z;
		}
		D3DXVECTOR3* actualChildMaxBounds;
		for (size_t i = 0; i < childrens.size(); i++)
		{
			actualChildMaxBounds = ((GameObject*)childrens[i])->GetGlobalMaxBounds();
			if (i == 0 && thisGameObjectMaxBounds == NULL) {
				x = actualChildMaxBounds->x;
				y = actualChildMaxBounds->y;
				z = actualChildMaxBounds->z;
			}
			if (actualChildMaxBounds->x > x) {
				x = actualChildMaxBounds->x;
			}
			if (actualChildMaxBounds->y > y) {
				y = actualChildMaxBounds->y;
			}
			if (actualChildMaxBounds->z > z) {
				z = actualChildMaxBounds->z;
			}
		}

		if (globalMaxBounds == NULL) {
			globalMaxBounds = new D3DXVECTOR3(x, y, z);
		}
		else {
			globalMaxBounds->x = x;
			globalMaxBounds->y = y;
			globalMaxBounds->z = z;
		}

		return globalMaxBounds;
	}
	D3DXVECTOR3* GetGlobalMinBounds() {
		float x = 0;
		float y = 0;
		float z = 0;
		D3DXVECTOR3* thisGameObjectMinBounds = GetGameObjectMinBounds();
		if (thisGameObjectMinBounds != NULL) {
			x = thisGameObjectMinBounds->x;
			y = thisGameObjectMinBounds->y;
			z = thisGameObjectMinBounds->z;
		}
		D3DXVECTOR3* actualChildMinBounds;
		for (size_t i = 0; i < childrens.size(); i++)
		{
			actualChildMinBounds = ((GameObject*)childrens[i])->GetGlobalMinBounds();
			
			if (i == 0 && thisGameObjectMinBounds == NULL) {
				x = actualChildMinBounds->x;
				y = actualChildMinBounds->y;
				z = actualChildMinBounds->z;
			}
			if (actualChildMinBounds->x < x) {
				x = actualChildMinBounds->x;
			}
			if (actualChildMinBounds->y < y) {
				y = actualChildMinBounds->y;
			}
			if (actualChildMinBounds->z < z) {
				z = actualChildMinBounds->z;
			}
		}

		if (globalMinBounds == NULL) {
			globalMinBounds = new D3DXVECTOR3(x, y, z);
		}
		else {
			globalMinBounds->x = x;
			globalMinBounds->y = y;
			globalMinBounds->z = z;
		}

		return globalMinBounds;
	}

	D3DXVECTOR3* GetGameObjectMaxBounds() {
		return personalMaxBounds;
	}
	D3DXVECTOR3* GetGameObjectMinBounds() {
		return personalMinBounds;
	}

	bool GetHasChange() {
		return hasChange;
	}


protected:
	Transform transform;
private:
	vector<Node*> components;
	vector<D3DXVECTOR3*> vertices;
	vector<D3DXVECTOR3*> globalVertices;
	D3DXVECTOR3 * personalMinBounds = NULL;
	D3DXVECTOR3 * personalMaxBounds = NULL;
	D3DXVECTOR3 * globalMinBounds = NULL;
	D3DXVECTOR3 * globalMaxBounds = NULL;
	bool hasSettedBounds = false;
	bool hasChange = false;

	void SetVerticesWithBounds() {
		for (int i = 0; i< vertices.size(); i++)
		{
			delete (vertices[i]);
		}
		vertices.clear();
		vertices.push_back(new D3DXVECTOR3(personalMinBounds->x, personalMinBounds->y, personalMinBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMaxBounds->x, personalMinBounds->y, personalMinBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMaxBounds->x, personalMaxBounds->y, personalMinBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMinBounds->x, personalMaxBounds->y, personalMinBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMinBounds->x, personalMinBounds->y, personalMaxBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMaxBounds->x, personalMinBounds->y, personalMaxBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMaxBounds->x, personalMaxBounds->y, personalMaxBounds->z));
		vertices.push_back(new D3DXVECTOR3(personalMinBounds->x, personalMaxBounds->y, personalMaxBounds->z));
	}
	void SetGlobalVerticesWithBounds() {
		for (int i = 0; i< globalVertices.size(); i++)
		{
			delete (globalVertices[i]);
		}
		globalVertices.clear();
		globalVertices.push_back(new D3DXVECTOR3(globalMinBounds->x, globalMinBounds->y, globalMinBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMaxBounds->x, globalMinBounds->y, globalMinBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMaxBounds->x, globalMaxBounds->y, globalMinBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMinBounds->x, globalMaxBounds->y, globalMinBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMinBounds->x, globalMinBounds->y, globalMaxBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMaxBounds->x, globalMinBounds->y, globalMaxBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMaxBounds->x, globalMaxBounds->y, globalMaxBounds->z));
		globalVertices.push_back(new D3DXVECTOR3(globalMinBounds->x, globalMaxBounds->y, globalMaxBounds->z));
	}
};

#endif // !GAMEOBJECT_H
