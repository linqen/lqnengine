#include "..\includes\Camera.h"
#include "..\includes\Component.h"

//Create a camera with default values
Camera::Camera(Graphics * rGraphics) : NodeWithChildren(rGraphics) {
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
	D3DXMatrixIdentity(&transform);
	localMatrix = worldMatrix = &transform;
}
//Create a camera specifying projection values
Camera::Camera(Graphics * rGraphics, float rAngleOnDegrees, float rNearPlane, float rFarPlane) : NodeWithChildren(rGraphics) {
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
	D3DXMatrixIdentity(&transform);
	localMatrix = worldMatrix = &transform;
}

void Camera::SetCameraAngle(float rAngleOnDegrees, float rNearPlane, float rFarPlane) {
	angleOnDegrees = rAngleOnDegrees;
	fAspectRatio = (float)graphics->viewport.Width / graphics->viewport.Height;
	nearPlane = rNearPlane;
	farPlane = rFarPlane;

	D3DXMatrixIdentity(mProjectionMatrix);
	D3DXMatrixPerspectiveFovLH(mProjectionMatrix, D3DXToRadian(angleOnDegrees), fAspectRatio, nearPlane, farPlane);
	graphics->SetProjectionMatrix(mProjectionMatrix);
}

void Camera::SetPosition(D3DXVECTOR3 Pos) {
	m_Position.x = Pos.x;
	m_Position.y = Pos.y;
	m_Position.z = Pos.z;
	m_bChanged = true;
}
void Camera::MoveForward(float Dist) {
	m_Position += Dist*m_LookAt;
	m_bChanged = true;
}
void Camera::MoveRight(float Dist) {
	m_Position += Dist*m_Right;
	m_bChanged = true;
}
void Camera::MoveUp(float Dist) {
	m_Position += Dist*m_Up;
	m_bChanged = true;
}
void Camera::MoveInDirection(float Dist, D3DXVECTOR3 *Dir) {
	m_Position += Dist*(*Dir);
	m_bChanged = true;
}
void Camera::Rotate(float x, float y, float z) {
	rotation->x += D3DXToRadian(x);
	rotation->y += D3DXToRadian(y);
	rotation->z += D3DXToRadian(z);
}
void Camera::Pitch(float Angle) {
	Rotate(Angle, 0, 0);
	m_RotateAroundRight += Angle;
	m_bChanged = true;
}
void Camera::Yaw(float Angle) {
	Rotate(0, Angle, 0);
	m_RotateAroundUp += Angle;
	m_bChanged = true;
}
void Camera::Roll(float Angle) {
	Rotate(0, 0, Angle);
	m_RotateAroundLookAt += Angle;
	m_bChanged = true;
}

void Camera::Update() {
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
	NodeWithChildren::Update();
}

void Camera::Draw() {

	D3DXMatrixIdentity(&transform);
	CameraDraw();
	NodeWithChildren::Draw(m_planes);
}

void Camera::AddComponent(Component* newComponent) {
	newComponent->SetParent(this);
	components.push_back(newComponent);
}

template <class Component>
Component* Camera::GetComponent()
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

bool Camera::RemoveComponent(Node* componentToRemove) { return true; }

void Camera::CameraDraw() {
	if (m_bChanged) {
		position->x = m_Position.x;
		position->y = m_Position.y;
		position->z = m_Position.z;
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
		//ConstructFrustumBox();
	}
	//Set view transform 
	graphics->SetViewTransform(m_MatView);
	//Reset update members
	m_RotateAroundRight = m_RotateAroundUp = m_RotateAroundLookAt = 0.0f;
	m_bChanged = false;

}
//This is normally used to make a FPS cam
void Camera::SetRightVectorYCoord(float y) {
	m_Right.y = y;

}

void Camera::ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix)
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
