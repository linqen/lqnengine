#include "..\includes\BSPPlane.h"

D3DXPLANE BSPPlane::GetPlane() {
	return plane;
}
void BSPPlane::SetPlane(D3DXPLANE rplane) {
	plane = rplane;
}

//Pointer to the start of the array of AmountOfVertices vertices
D3DXVECTOR3* BSPPlane::GetVertices() {
	return &vertices[0];
}

//Pointer to the start of the array of AmountOfVertices vertices
void BSPPlane::SetVertices(D3DXVECTOR3* firstVertex) {
	for (size_t i = 0; i < AmountOfVertices; i++)
	{
		vertices[i] = firstVertex[i];
	}
}
