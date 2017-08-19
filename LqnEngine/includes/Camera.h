#ifndef CAMERA_H
#define CAMERA_H
#include "ImportExport.h"
#include "Graphics.h"
#include <d3dx9.h>
class LQN_API Camera {
public:
	//Create a camera with default values
	Camera(Graphics * rGraphics) {
		graphics = rGraphics;
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		//Set position to 0,0,0 
		m_LookAt = D3DXVECTOR3(0.0f,0.0f,1.0f); 
		//Set look at to 0,0,1 
		m_Right = D3DXVECTOR3(1.0f,0.0f,0.0f); 
		//Set right to 1,0,0 
		m_Up = D3DXVECTOR3(0.0f,1.0f,0.0f); 
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
	Camera(Graphics * rGraphics, float rAngleOnDegrees, float rNearPlane, float rFarPlane) {
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

	void SetPosition(D3DXVECTOR3 *Pos) {
		m_Position = *Pos; 
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
	void Pich(float Angle) { 
		m_RotateAroundRight += Angle; 
		m_bChanged = true; 
	}
	void Yaw(float Angle) {
		m_RotateAroundUp += Angle;
		m_bChanged = true; 
	}
	void Roll(float Angle) {
		m_RotateAroundLookAt += Angle;
		m_bChanged = true; 
	}

	void Update() {
		if (m_bChanged) { 
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
			float fView41,fView42,fView43;
			fView41 = -D3DXVec3Dot(&m_Right, &m_Position);
			fView42 = -D3DXVec3Dot(&m_Up, &m_Position);
			fView43 = -D3DXVec3Dot(&m_LookAt, &m_Position);
			//Fill in the view matrix 
			m_MatView = new D3DXMATRIX(
				m_Right.x, m_Up.x, m_LookAt.x, 0.0f,
				m_Right.y, m_Up.y, m_LookAt.y, 0.0f,
				m_Right.z, m_Up.z, m_LookAt.z, 0.0f,
				fView41, fView42, fView43, 1.0f);
		}
		//Set view transform 
		graphics->SetViewTransform(m_MatView);
		//Reset update members
		m_RotateAroundRight = m_RotateAroundUp = m_RotateAroundLookAt = 0.0f;
		m_bChanged = false;
	}

private:
	Graphics * graphics;
	//Proyection related variables
	float fAspectRatio;
	float angleOnDegrees;
	float nearPlane, farPlane;
	D3DXMATRIX * mProjectionMatrix;

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
	//Final view transformation matrix 
	D3DXMATRIX * m_MatView;

};
#endif