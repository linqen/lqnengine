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
	//xPos += 3;
	//yScale += 0.01f;
	//xScale += 0.01f;
	//zRot += 0.005f;
	graphics->LoadIdentity();
	graphics->Translate(xPos, yPos, zPos);
	graphics->RotateZ(zRot);
	graphics->Scale(xScale, yScale, zScale);
}