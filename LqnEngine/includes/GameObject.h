#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ImportExport.h"
#include "NodeWithChildren.h"

class LQN_API GameObject : public NodeWithChildren {
public:
	GameObject(Graphics * graphics);

	virtual void Update();
	virtual void Draw(D3DXPLANE* frustumPlane, vector<BSPPlane*> BSPPlanes, vector<int> cameraBSPRelationWithPlane);
	bool CheckIsInFrustum(D3DXPLANE* frustumPlane, vector<D3DXVECTOR3*> m_vertices, int debugValue);
	bool CheckBSP(vector<BSPPlane*> BSPPlanes, vector<int> cameraBSPRelationWithPlane, vector<D3DXVECTOR3*> m_vertices);
	void AddComponent(Component* newComponent);

	template <class Component>
	Component* GetComponent();
	bool RemoveComponent(Node* componentToRemove);
	void SetGameObjectMinBounds(D3DXVECTOR3* gameObjectMinBounds);
	void SetGameObjectMaxBounds(D3DXVECTOR3* gameObjectMaxBounds);
	D3DXVECTOR3* CalculateGlobalMaxBounds();
	D3DXVECTOR3* CalculateGlobalMinBounds();
	D3DXVECTOR3* GetGlobalMaxBounds();
	D3DXVECTOR3* GetGlobalMinBounds();
	D3DXVECTOR3* GetGameObjectMaxBounds();
	D3DXVECTOR3* GetGameObjectMinBounds();
	D3DXMATRIX* GetWorldMatrix();
	void SetBSPPlanes(vector<BSPPlane*> BSP_Planes);
	vector<NodeWithChildren*> GetChilds();
	GameObject* GetChildByName(string name);

protected:
	Transform transform;
private:
	bool hasBSPPlanes = false;
	vector<BSPPlane*> BSPPlanes;
	vector<Component*> components;
	vector<D3DXVECTOR3*> vertices;
	vector<D3DXVECTOR3*> globalVertices;
	D3DXVECTOR3 * personalMinBounds = NULL;
	D3DXVECTOR3 * personalMaxBounds = NULL;
	D3DXVECTOR3 * globalMinBounds = NULL;
	D3DXVECTOR3 * globalMaxBounds = NULL;
	bool hasSettedBounds = false;

	void SetVerticesWithBounds();
	void SetGlobalVerticesWithBounds();
};

#endif // !GAMEOBJECT_H
