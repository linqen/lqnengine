#ifndef NODEWITHCHILDREN_H
#define NODEWITHCHILDREN_H
#define PI 3.14159265358979323846
#include "ImportExport.h"
#include <vector>
#include "Node.h"
#include "BSPPlane.h"
class Component;

typedef D3DXMATRIX Transform;
class LQN_API NodeWithChildren : public Node {
public:
	NodeWithChildren(Graphics *graphics) : Node (graphics) {
		position = new D3DXVECTOR3(0, 0, 0);
		rotation = new D3DXVECTOR3(0, 0, 0);
		scale = new D3DXVECTOR3(1, 1, 1);
		localPosition = new D3DXVECTOR3(0, 0, 0);
		localRotation = new D3DXVECTOR3(0, 0, 0);
		localScale = new D3DXVECTOR3(1, 1, 1);
		localMatrix = new D3DXMATRIX();
		rotationQuaternion = new D3DXQUATERNION();
		localRotationQuaternion = new D3DXQUATERNION();
	}
	~NodeWithChildren() {}

	void SetName(const string& n) {
		name = n;
	}

	string& GetName() {
		return name;
	}

	virtual void Update() {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Update();
		}
		Node::Update();
	}
	virtual void Draw(D3DXPLANE* frustumPlane, vector<BSPPlane*> BSPPlanes, vector<int> cameraBSPRelationWithPlane) {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Draw(frustumPlane, BSPPlanes, cameraBSPRelationWithPlane);

		}
		Node::Draw();

	}

	void SetParent(NodeWithChildren * nodeWithChildren) {
		parent = nodeWithChildren;
	}

	void AddChildren(NodeWithChildren* newNode) {
		newNode->SetParent(this);
		childrens.push_back(newNode);
	}

	bool RemoveChildren(NodeWithChildren* nodeToRemove) { return true; }

	void Translate(float x, float y, float z) {
		position->x += x;
		position->y += y;
		position->z += z;
		ApplyChangesToLocalMatrix();
	}

	void Rotate(float x, float y, float z) {
		rotation->x += D3DXToRadian(x);
		rotation->y += D3DXToRadian(y);
		rotation->z += D3DXToRadian(z);
		ApplyChangesToLocalMatrix();
	}

	void SetPosition(float x, float y, float z) {
		position->x = x;
		position->y = y;
		position->z = z;
		ApplyChangesToLocalMatrix();
	}


	void SetRotation(float x, float y, float z) {
		rotation->x = D3DXToRadian(x);
		rotation->y = D3DXToRadian(y);
		rotation->z = D3DXToRadian(z);
		ApplyChangesToLocalMatrix();
	}


	void SetScale(float x, float y, float z) {
		scale->x = x;
		scale->y = y;
		scale->z = z;
		ApplyChangesToLocalMatrix();
	}

	void SetLocalPosition(float x, float y, float z) {
		localPosition->x = x;
		localPosition->y = y;
		localPosition->z = z;
		ApplyChangesToWorldMatrix();
	}


	void SetLocalRotation(float x, float y, float z) {
		localRotation->x = D3DXToRadian(x);
		localRotation->y = D3DXToRadian(y);
		localRotation->z = D3DXToRadian(z);
		ApplyChangesToWorldMatrix();
	}


	void SetLocalScale(float x, float y, float z) {
		localScale->x = x;
		localScale->y = y;
		localScale->z = z;
		ApplyChangesToWorldMatrix();
	}


	D3DXVECTOR3 GetPosition() {
		return D3DXVECTOR3(position->x, position->y, position->z);
	}


	D3DXVECTOR3 GetRotation() {
		return D3DXVECTOR3(rotation->x, rotation->y, rotation->z);
	}


	D3DXVECTOR3 GetScale() {
		return D3DXVECTOR3(scale->x, scale->y, scale->z);
	}


	D3DXVECTOR3 GetLocalPosition() {
		return D3DXVECTOR3(localPosition->x, localPosition->y, localPosition->z);
	}


	D3DXVECTOR3 GetLocalRotation() {
		return D3DXVECTOR3(localRotation->x, localRotation->y, localRotation->z);
	}


	D3DXVECTOR3 GetLocalScale() {
		return D3DXVECTOR3(localScale->x, localScale->y, localScale->z);
	}

	bool GetHasChange() {
		return hasChange;
	}

	void ApplyChangesToWorldMatrix() {
		D3DXMatrixTransformation(localMatrix, NULL, NULL, localScale, NULL, D3DXQuaternionRotationYawPitchRoll(localRotationQuaternion, localRotation->z, localRotation->y, localRotation->x), localPosition);
		worldMatrix = CalculateWorldMatrixBasedOnParent();
		D3DXMatrixDecompose(scale, rotationQuaternion, position, worldMatrix);
	}
	void ApplyChangesToLocalMatrix() {
		D3DXMatrixTransformation(worldMatrix, NULL, NULL, scale, NULL, D3DXQuaternionRotationYawPitchRoll(rotationQuaternion, rotation->z, rotation->y, rotation->x), position);
		localMatrix = CalculateLocalMatrixBasedOnParent();
		D3DXMatrixDecompose(localScale, localRotationQuaternion, localPosition, localMatrix);

		QuaterniontoEulerAngle(*localRotationQuaternion, localRotation);
	}
protected:
	NodeWithChildren* parent = NULL;
	D3DXMATRIX * localMatrix = NULL;
	D3DXMATRIX * worldMatrix = NULL;
	D3DXVECTOR3* position;
	D3DXVECTOR3* rotation;
	D3DXVECTOR3* scale;
	D3DXVECTOR3* localPosition;
	D3DXVECTOR3* localRotation;
	D3DXVECTOR3* localScale;
	D3DXQUATERNION * rotationQuaternion = NULL;
	D3DXQUATERNION * localRotationQuaternion = NULL;
	bool hasChange = false;
	bool hasChangeLocally = false;
	string name;
	Transform * transform;
	vector<NodeWithChildren*> childrens;

	D3DXMATRIX* CalculateWorldMatrixBasedOnParent() {
		if (parent != NULL) {
			D3DXMATRIX* parentWorldMatrix = parent->worldMatrix;
			return D3DXMatrixMultiply(worldMatrix, localMatrix, parentWorldMatrix);
		}
		else {
			return localMatrix;
		}
	}

	D3DXMATRIX* CalculateLocalMatrixBasedOnParent() {
		if (parent != NULL) {
			D3DXMATRIX* parentWorldMatrix = parent->worldMatrix;
			D3DXMATRIX parentInvertedMatrix = D3DXMATRIX();
			parentInvertedMatrix = *D3DXMatrixInverse(&parentInvertedMatrix, NULL, parentWorldMatrix);
			return D3DXMatrixMultiply(localMatrix, worldMatrix, &parentInvertedMatrix);
		}
		else {
			return worldMatrix;
		}
	}
private:
	void QuaterniontoEulerAngle(const D3DXQUATERNION& q, D3DXVECTOR3* rotation)
	{
		// roll (x-axis rotation)
		double sinr = +2.0 * (q.w * q.x + q.y * q.z);
		double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
		rotation->z = atan2(sinr, cosr);

		// pitch (y-axis rotation)
		double sinp = +2.0 * (q.w * q.y - q.z * q.x);
		if (fabs(sinp) >= 1)
			rotation->x = copysign(PI / 2, sinp); // use 90 degrees if out of range
		else
			rotation->x = asin(sinp);

		// yaw (z-axis rotation)
		double siny = +2.0 * (q.w * q.z + q.x * q.y);
		double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
		rotation->y = atan2(siny, cosy);
	}
};


#endif