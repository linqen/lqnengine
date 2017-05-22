#include "..\includes\Entity2D.h"
#include <timeapi.h>

Entity2D::Entity2D(Graphics *graphics) {
	this->graphics = graphics;
	this->xPos = 0;
	this->yPos = 0;
	this->zPos = 0;
	this->zRot = 0;
	this->xScale = 1;
	this->yScale = 1;
	this->zScale = 1;
}

void Entity2D::Update() {

}

void Entity2D::Draw() {
	xPos += 10;
	//xScale += 0.01f;
	//zRot += 0.005f;
	graphics->LoadIdentity();
	graphics->Translate(xPos, yPos, zPos);
	graphics->RotateZ(zRot);
	graphics->Scale(xScale, yScale, zScale);


	//D3DXMatrixIdentity(&graphics->d3dmat);
	//FLOAT fAngle = 50.0f * (2.0f * D3DX_PI) / 1000.0f;
	//fAngle += 2.0f;
	//D3DXMatrixRotationZ(&graphics->d3dmat, fAngle);
	//graphics->pd3dDevice->SetTransform(D3DTS_WORLD, &graphics->d3dmat);

	// SET UP THE PIPELINE

	//D3DXMATRIX matRotateZ;    // a matrix to store the rotation information


	//											  // build a matrix to rotate the model based on the increasing float value
	//D3DXMatrixRotationZ(&matRotateZ, index);

	//// tell Direct3D about our matrix
	//graphics->pd3dDevice->SetTransform(D3DTS_WORLD, &matRotateZ);


	//Reseteamos seteando a identidad
	//D3DXMATRIX d3dmat;
	//D3DXMatrixIdentity(&d3dmat);
	//graphics->pd3dDevice->SetTransform(D3DTS_WORLD, &d3dmat);

	////Transladamos
	//D3DXMatrixTranslation(&d3dmat, xPos, yPos, zPos);

	//graphics->pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
	////Rotamos
	//D3DXMatrixRotationX(&d3dmat, xRot);
	//graphics->pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
	//D3DXMatrixRotationY(&d3dmat, yRot);
	//graphics->pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
	//D3DXMatrixRotationZ(&d3dmat, zRot);
	//graphics->pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);

	////Escalamos
	//D3DXMatrixScaling(&d3dmat, xScale, yScale, zScale);

	//graphics->pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);

	//Cada vez que dibujamos, antes de hacerlo cargamos matriz identidad, 
	//luego trasladamos, rotamos, y por último escalamos
	//	renderer.loadentity 
	//	renderer.translate{
	//	d3dxmatrixtranslation(&_theMatrix,fx,fy,fz)
	//	pd3ddivece-< ultriply transform d3dts_worldmatrix, fx,fy,fz)
	//
	//}
	//	renderer.rotationZ
	//	renderer.scale


	//	SHPAE

	//	entity2d.draw
	//	renderer.draw
}