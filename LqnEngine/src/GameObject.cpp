#include "..\includes\GameObject.h"
#include "..\includes\Component.h"


GameObject::GameObject(Graphics * graphics) :NodeWithChildren(graphics) {
	localMatrix = D3DXMatrixTransformation(localMatrix, NULL, NULL, localScale, NULL,
		D3DXQuaternionRotationYawPitchRoll(localRotationQuaternion, localRotation->y, localRotation->x, localRotation->z),
		localPosition);
	worldMatrix = CalculateWorldMatrixBasedOnParent();
	D3DXMatrixDecompose(scale, rotationQuaternion, position, worldMatrix);

	SetGameObjectMinBounds(new D3DXVECTOR3(this->position->x, this->position->y, this->position->z));
	SetGameObjectMaxBounds(new D3DXVECTOR3(this->position->x, this->position->y, this->position->z));
};

void GameObject::Update() {
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}

	localMatrix = D3DXMatrixTransformation(localMatrix, NULL, NULL, localScale, NULL,
		D3DXQuaternionRotationYawPitchRoll(localRotationQuaternion, localRotation->y, localRotation->x, localRotation->z),
		localPosition);
	worldMatrix = CalculateWorldMatrixBasedOnParent();
	D3DXMatrixDecompose(scale, rotationQuaternion, position, worldMatrix);

	//THIS WORKS?
	//D3DXQuaternionToAxisAngle(rotationQuaternion, rotation, NULL);
	//Just in case that the GameObject dont have mesh
	*personalMaxBounds = *personalMinBounds = D3DXVECTOR3(position->x, position->y, position->z);
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->CalculateBounds();
	}
	NodeWithChildren::Update();

	//Chequear aplicar cambios al quaternion y llevar el quaternion a los vectores correctamente
	globalMaxBounds = CalculateGlobalMaxBounds();
	globalMinBounds = CalculateGlobalMinBounds();
}

void GameObject::Draw(D3DXPLANE* frustumPlane) {
	SetGlobalVerticesWithBounds();
	if (CheckIsInFrustum(frustumPlane, globalVertices, 1)) {
		SetVerticesWithBounds();
		if (GetGameObjectMinBounds() != NULL && GetGameObjectMaxBounds() != NULL &&
			CheckIsInFrustum(frustumPlane, vertices, 2)) {
			for (size_t i = 0; i < components.size(); i++)
			{
				components[i]->Draw();
			}
		}
		NodeWithChildren::Draw(frustumPlane);
	}
	hasChange = false;
	hasChangeLocally = false;
	hasSettedBounds = false;
}

bool GameObject::CheckIsInFrustum(D3DXPLANE* frustumPlane, vector<D3DXVECTOR3*> m_vertices, int debugValue) {
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
			wstring fileName(L"Ocultando en Frustum\n" + to_wstring(debugValue) + wstring(name.begin(), name.end()));
			LPCWSTR fullPath = fileName.c_str();
			OutputDebugString(fullPath);
			return false;
		}
	}
	return true;
}

void GameObject::AddComponent(Component* newComponent) {
	newComponent->SetParent(this);
	components.push_back(newComponent);
}

template <class Component>
Component* GameObject::GetComponent()
{
	Component* actualComponent;
	for (size_t i = 0; i < components.size(); i++)
	{
		actualComponent = dynamic_cast<Component*>(components[i]);
		if (actualComponent != nullptr) {
			return actualComponent;
		}
	}
	return NULL;
}

bool GameObject::RemoveComponent(Node* componentToRemove) { return true; }

void GameObject::SetGameObjectMinBounds(D3DXVECTOR3* gameObjectMinBounds) {
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

void GameObject::SetGameObjectMaxBounds(D3DXVECTOR3* gameObjectMaxBounds) {
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

D3DXVECTOR3* GameObject::CalculateGlobalMaxBounds() {
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
D3DXVECTOR3* GameObject::CalculateGlobalMinBounds() {
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

D3DXVECTOR3* GameObject::GetGameObjectMaxBounds() {
	return personalMaxBounds;
}
D3DXVECTOR3* GameObject::GetGameObjectMinBounds() {
	return personalMinBounds;
}
D3DXVECTOR3* GameObject::GetGlobalMaxBounds() {
	return globalMaxBounds;
}
D3DXVECTOR3* GameObject::GetGlobalMinBounds() {
	return globalMinBounds;
}

D3DXMATRIX* GameObject::GetWorldMatrix() {
	return worldMatrix;
}

void GameObject::SetVerticesWithBounds() {
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
void GameObject::SetGlobalVerticesWithBounds() {
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
