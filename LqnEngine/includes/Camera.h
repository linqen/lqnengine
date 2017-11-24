#ifndef CAMERA_H
#define CAMERA_H
#include "ImportExport.h"
#include "Graphics.h"
#include "NodeWithChildren.h"
#include <d3dx9.h>
class LQN_API Camera : public NodeWithChildren {
public:
	//Create a camera with default values
	Camera(Graphics * rGraphics) : NodeWithChildren(rGraphics) {
		graphics = rGraphics;
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//Set position to 0,0,0 
		m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//Set look at to 0,0,1 
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		//Set right to 1,0,0 
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//Set up to 0,1,0 
		m_RotateAroundUp = m_RotateAroundRight = m_RotateAroundLookAt = 0;
		m_MatView = new D3DXMATRIX();
		D3DXMatrixIdentity(m_MatView);

		//Set Defaults projection values
		angleOnDegrees = D3DXToRadian(60);
		nearPlane = 0.1f;
		farPlane = 1000.0f;
		mProjectionMatrix = new D3DXMATRIX();
		SetCameraAngle(angleOnDegrees, nearPlane, farPlane);
	}
	//Create a camera specifying projection values
	Camera(Graphics * rGraphics, float rAngleOnDegrees, float rNearPlane, float rFarPlane) : NodeWithChildren(rGraphics) {
		graphics = rGraphics;
		//Projection
		nearPlane = rNearPlane;
		farPlane = rFarPlane;
		angleOnDegrees = rAngleOnDegrees;
		mProjectionMatrix = new D3DXMATRIX();
		SetCameraAngle(angleOnDegrees, nearPlane, farPlane);

		//View
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		m_RotateAroundUp = m_RotateAroundRight = m_RotateAroundLookAt = 0;
		m_MatView = new D3DXMATRIX();
		D3DXMatrixIdentity(m_MatView);
		ConstructFrustumBox();
	}

	void SetCameraAngle(float rAngleOnDegrees, float rNearPlane, float rFarPlane) {
		angleOnDegrees = rAngleOnDegrees;
		fAspectRatio = (float)graphics->viewport.Width / graphics->viewport.Height;
		nearPlane = rNearPlane;
		farPlane = rFarPlane;

		D3DXMatrixIdentity(mProjectionMatrix);
		D3DXMatrixPerspectiveFovLH(mProjectionMatrix, D3DXToRadian(angleOnDegrees), fAspectRatio, nearPlane, farPlane);
		graphics->SetProjectionMatrix(mProjectionMatrix);
	}

	void SetPosition(D3DXVECTOR3 Pos) {
		m_Position.x = Pos.x;
		m_Position.y = Pos.y;
		m_Position.z = Pos.z;
		m_bChanged = true;
	}
	void MoveForward(float Dist) {
		m_Position += Dist*m_LookAt;
		m_bChanged = true;
	}
	void MoveRight(float Dist) {
		m_Position += Dist*m_Right;
		m_bChanged = true;
	}
	void MoveUp(float Dist) {
		m_Position += Dist*m_Up;
		m_bChanged = true;
	}
	void MoveInDirection(float Dist, D3DXVECTOR3 *Dir) {
		m_Position += Dist*(*Dir);
		m_bChanged = true;
	}
	void Pitch(float Angle) {
		xRot += Angle;
		m_RotateAroundRight += Angle;
		m_bChanged = true;
	}
	void Yaw(float Angle) {
		yRot += Angle;
		m_RotateAroundUp += Angle;
		m_bChanged = true;
	}
	void Roll(float Angle) {
		zRot += Angle;
		m_RotateAroundLookAt += Angle;
		m_bChanged = true;
	}

	virtual void Update() {
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update();
		}
		NodeWithChildren::Update();
	}

	virtual void Draw() {

		D3DXMatrixIdentity(&transform);
		graphics->SetWorldTransform(&transform);
		CameraDraw();
		NodeWithChildren::Draw(m_planes, &frustumBoxMinBounds, &frustumBoxMaxBounds);
	}

	void AddComponent(Node* newComponent) {
		newComponent->SetParent(this);
		components.push_back(newComponent);
	}

	bool RemoveComponent(Node* componentToRemove) { return true; }

	void CameraDraw() {
		if (m_bChanged) {
			xPos = m_Position.x;
			yPos = m_Position.y;
			zPos = m_Position.z;
			//Matrices to store the transformations about our axes 
			D3DXMATRIX MatTotal;
			D3DXMATRIX MatRotateAroundRight;
			D3DXMATRIX MatRotateAroundUp;
			D3DXMATRIX MatRotateAroundLookAt;
			//Get the matrix for each rotation 
			D3DXMatrixRotationAxis(&MatRotateAroundRight, &m_Right, m_RotateAroundRight);
			D3DXMatrixRotationAxis(&MatRotateAroundUp, &m_Up, m_RotateAroundUp);
			D3DXMatrixRotationAxis(&MatRotateAroundLookAt, &m_LookAt, m_RotateAroundLookAt);
			//Combine the transformations into one matrix
			D3DXMatrixMultiply(&MatTotal, &MatRotateAroundUp, &MatRotateAroundRight);
			D3DXMatrixMultiply(&MatTotal, &MatRotateAroundLookAt, &MatTotal);
			//Transforms two vectors by our matrix and computes the third by 
			//cross product
			D3DXVec3TransformCoord(&m_Right, &m_Right, &MatTotal);
			D3DXVec3TransformCoord(&m_Up, &m_Up, &MatTotal);
			D3DXVec3Cross(&m_LookAt, &m_Right, &m_Up);
			//Check to ensure vectors are perpendicular 
			if (fabs(D3DXVec3Dot(&m_Up, &m_Right)) > 0.01) {
				//If they’re not 
				D3DXVec3Cross(&m_Up, &m_LookAt, &m_Right);
			}
			//Normalize our vectors
			D3DXVec3Normalize(&m_Right, &m_Right);
			D3DXVec3Normalize(&m_Up, &m_Up);
			D3DXVec3Normalize(&m_LookAt, &m_LookAt);
			//Compute the bottom row of the view matrix 
			float fView41, fView42, fView43;
			fView41 = -D3DXVec3Dot(&m_Right, &m_Position);
			fView42 = -D3DXVec3Dot(&m_Up, &m_Position);
			fView43 = -D3DXVec3Dot(&m_LookAt, &m_Position);
			//Fill in the view matrix 
			m_MatView = new D3DXMATRIX(
				m_Right.x, m_Up.x, m_LookAt.x, 0.0f,
				m_Right.y, m_Up.y, m_LookAt.y, 0.0f,
				m_Right.z, m_Up.z, m_LookAt.z, 0.0f,
				fView41, fView42, fView43, 1.0f);


			ConstructFrustum(farPlane, *mProjectionMatrix, *m_MatView);
			ConstructFrustumBox();
		}
		//Set view transform 
		graphics->SetViewTransform(m_MatView);
		//Reset update members
		m_RotateAroundRight = m_RotateAroundUp = m_RotateAroundLookAt = 0.0f;
		m_bChanged = false;

	}
	//This is normally used to make a FPS cam
	void SetRightVectorYCoord(float y) {
		m_Right.y = y;

	}

	//D3DXVECTOR3 frustumBoxMinBounds;
	//D3DXVECTOR3 frustumBoxMaxBounds;

	D3DXVECTOR3* GetFrustMaxBound() {
		return &frustumBoxMaxBounds;
	}
	D3DXVECTOR3* GetFrustMinBound() {
		return &frustumBoxMinBounds;
	}

	Transform transform;
private:
	vector<Node*> components;
	Graphics * graphics;
	//Proyection related variables
	float fAspectRatio;
	float angleOnDegrees;
	float nearPlane, farPlane;
	D3DXMATRIX * mProjectionMatrix;
	//Final view transformation matrix 
	D3DXMATRIX * m_MatView;

	//View related variables
	//Stores the position and three vectors 
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_LookAt;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Up;
	//Stores whether the camera has changed since last update.
	//By change, we mean whether the camera has moved 
	//or rotated. If so, we’ll recompute the matrix. 
	bool m_bChanged;
	//Stores the rotation to apply to a given axis 
	float m_RotateAroundUp;
	float m_RotateAroundRight;
	float m_RotateAroundLookAt;
	//frustumCulling
	float arcTangFOV = 0;
	D3DXVECTOR3 frustumBoxMinBounds;
	D3DXVECTOR3 frustumBoxMaxBounds;
	D3DXPLANE m_planes[6];
	D3DXVECTOR3 * frustumVertices[5];

	void ConstructFrustumBox() {
		if (arcTangFOV == 0) {
			arcTangFOV = atan(D3DXToRadian(angleOnDegrees));
		}
		frustumBoxMaxBounds = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//Roto el vector
		//D3DXVEC
		D3DXMATRIX rotationMatrix;
		D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(angleOnDegrees));
		D3DXVECTOR4 temporalMaxBounds;
		D3DXVec3Transform(&temporalMaxBounds, &frustumBoxMaxBounds, &rotationMatrix);

		//frustumBoxMaxBounds
		temporalMaxBounds *= arcTangFOV*farPlane;
		temporalMaxBounds.y = temporalMaxBounds.x*((float)graphics->viewport.Height / graphics->viewport.Width);
		temporalMaxBounds.z = sqrt(pow(temporalMaxBounds.x, 2) + pow(farPlane, 2));

		frustumVertices[0] = new D3DXVECTOR3(temporalMaxBounds.x, temporalMaxBounds.y, temporalMaxBounds.z);
		frustumVertices[1] = new D3DXVECTOR3(temporalMaxBounds.x, -temporalMaxBounds.y, temporalMaxBounds.z);
		frustumVertices[2] = new D3DXVECTOR3(-temporalMaxBounds.x, temporalMaxBounds.y, temporalMaxBounds.z);
		frustumVertices[3] = new D3DXVECTOR3(-temporalMaxBounds.x, -temporalMaxBounds.y, temporalMaxBounds.z);
		frustumVertices[4] = new D3DXVECTOR3(0, 0, 0);

		//Traslate bounds to real position
		graphics->PushCurrentlMatrix();
		graphics->LoadIdentity();
		graphics->Translate(xPos, yPos, zPos);
		graphics->RotateX(xRot);
		graphics->RotateY(yRot);
		graphics->RotateZ(zRot);
		graphics->Scale(xScale, yScale, zScale);

		for (int i = 0; i < 5; i++)
		{
			D3DXVec3Transform(&temporalMaxBounds, frustumVertices[i], &graphics->d3dmat);
			//Generate Max bounds of the box
			if (i == 0)
			{
				frustumBoxMaxBounds.x = temporalMaxBounds.x;
				frustumBoxMaxBounds.y = temporalMaxBounds.y;
				frustumBoxMaxBounds.z = temporalMaxBounds.z;
			}
			else
			{
				if (frustumBoxMaxBounds.x < temporalMaxBounds.x) {
					frustumBoxMaxBounds.x = temporalMaxBounds.x;
				}
				if (frustumBoxMaxBounds.y < temporalMaxBounds.y) {
					frustumBoxMaxBounds.y = temporalMaxBounds.y;
				}
				if (frustumBoxMaxBounds.z < temporalMaxBounds.z) {
					frustumBoxMaxBounds.z = temporalMaxBounds.z;
				}
			}
			//Generate Min bounds of the box
			if (i == 0)
			{
				frustumBoxMinBounds.x = temporalMaxBounds.x;
				frustumBoxMinBounds.y = temporalMaxBounds.y;
				frustumBoxMinBounds.z = temporalMaxBounds.z;
			}
			else
			{
				if (frustumBoxMinBounds.x > temporalMaxBounds.x) {
					frustumBoxMinBounds.x = temporalMaxBounds.x;
				}
				if (frustumBoxMinBounds.y > temporalMaxBounds.y) {
					frustumBoxMinBounds.y = temporalMaxBounds.y;
				}
				if (frustumBoxMinBounds.z > temporalMaxBounds.z) {
					frustumBoxMinBounds.z = temporalMaxBounds.z;
				}
			}
		}
		graphics->PopLastMatrix();

	}

	void ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix)
	{
		float zMinimum, r;
		D3DXMATRIX matrix;


		// Calculate the minimum Z distance in the frustum.
		zMinimum = -projectionMatrix._43 / projectionMatrix._33;
		r = screenDepth / (screenDepth - zMinimum);
		projectionMatrix._33 = r;
		projectionMatrix._43 = -r * zMinimum;

		// Create the frustum matrix from the view matrix and updated projection matrix.
		D3DXMatrixMultiply(&matrix, &viewMatrix, &projectionMatrix);

		// Calculate near plane of frustum.
		m_planes[0].a = matrix._14 + matrix._13;
		m_planes[0].b = matrix._24 + matrix._23;
		m_planes[0].c = matrix._34 + matrix._33;
		m_planes[0].d = matrix._44 + matrix._43;
		D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

		// Calculate far plane of frustum.
		m_planes[1].a = matrix._14 - matrix._13;
		m_planes[1].b = matrix._24 - matrix._23;
		m_planes[1].c = matrix._34 - matrix._33;
		m_planes[1].d = matrix._44 - matrix._43;
		D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

		// Calculate left plane of frustum.
		m_planes[2].a = matrix._14 + matrix._11;
		m_planes[2].b = matrix._24 + matrix._21;
		m_planes[2].c = matrix._34 + matrix._31;
		m_planes[2].d = matrix._44 + matrix._41;
		D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

		// Calculate right plane of frustum.
		m_planes[3].a = matrix._14 - matrix._11;
		m_planes[3].b = matrix._24 - matrix._21;
		m_planes[3].c = matrix._34 - matrix._31;
		m_planes[3].d = matrix._44 - matrix._41;
		D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

		// Calculate top plane of frustum.
		m_planes[4].a = matrix._14 - matrix._12;
		m_planes[4].b = matrix._24 - matrix._22;
		m_planes[4].c = matrix._34 - matrix._32;
		m_planes[4].d = matrix._44 - matrix._42;
		D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

		// Calculate bottom plane of frustum.
		m_planes[5].a = matrix._14 + matrix._12;
		m_planes[5].b = matrix._24 + matrix._22;
		m_planes[5].c = matrix._34 + matrix._32;
		m_planes[5].d = matrix._44 + matrix._42;
		D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);

		return;
	}



};
#endif