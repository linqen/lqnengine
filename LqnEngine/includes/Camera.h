#ifndef CAMERA_H
#define CAMERA_H
#include "ImportExport.h"
#include "Graphics.h"
#include "NodeWithChildren.h"
#include <d3dx9.h>

class LQN_API Camera : public NodeWithChildren {
public:
	//Create a camera with default values
	Camera(Graphics * rGraphics);
	//Create a camera specifying projection values
	Camera(Graphics * rGraphics, float rAngleOnDegrees, float rNearPlane, float rFarPlane);

	void SetCameraAngle(float rAngleOnDegrees, float rNearPlane, float rFarPlane);

	void SetPosition(D3DXVECTOR3 Pos);
	void MoveForward(float Dist);
	void MoveRight(float Dist);
	void MoveUp(float Dist);
	void MoveInDirection(float Dist, D3DXVECTOR3 *Dir);
	void Pitch(float Angle);
	void Yaw(float Angle);
	void Roll(float Angle);
	void Rotate(float x, float y, float z);
	void SetBSPPlanes(vector<BSPPlane*> BSPPlanes);
	void CalculateBSPRelation();

	virtual void Update();

	virtual void Draw();

	void AddComponent(Component* newComponent);

	template <class Component>
	Component* GetComponent();

	bool RemoveComponent(Node* componentToRemove);

	void CameraDraw();
	//This is normally used to make a FPS cam
	void SetRightVectorYCoord(float y);

	Transform transform;
private:
	vector<BSPPlane*> BSP_planes;
	vector<int> relationWithPlane;
	vector<Component*> components;
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
	D3DXPLANE m_planes[6];
	D3DXVECTOR3 * frustumVertices[5];

	void ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix);



};
#endif