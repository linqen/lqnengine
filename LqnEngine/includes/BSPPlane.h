#ifndef BSPPLANE_H
#define BSPPLANE_H
#define AMOUNTOFVERTICES 3
#include "ImportExport.h"

#include <d3d9.h>
#include <d3dx9.h>
class LQN_API BSPPlane {
public:
	static const int AmountOfVertices = AMOUNTOFVERTICES;
	D3DXPLANE GetPlane();
	void SetPlane(D3DXPLANE rplane);

	//Pointer to the start of the array of AmountOfVertices vertices
	D3DXVECTOR3* GetVertices();

	//Pointer to the start of the array of AmountOfVertices vertices
	void SetVertices(D3DXVECTOR3* firstVertex);

private:
	D3DXPLANE plane;
	D3DXVECTOR3 vertices[AmountOfVertices];

};
#endif