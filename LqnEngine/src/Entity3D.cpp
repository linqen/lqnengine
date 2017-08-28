#include "..\includes\Entity3D.h"
#include <timeapi.h>

Entity3D::Entity3D(Graphics *graphics) {
	this->graphics = graphics;
	this->xPos = 0;
	this->yPos = 0;
	this->zPos = 0;
	this->zRot = 0;
	this->xScale = 1;
	this->yScale = 1;
	this->zScale = 1;
	this->width = 10;
	this->height = 10;
	this->collisionWidth = width * 2;
	this->collisionHeight = height * 2;
	this->mass = 1;
	this->isKinematic = false;
	this->isTrigger = false;
}

void Entity3D::Update() {

}

void Entity3D::Draw() {
	graphics->LoadIdentity();
	graphics->Translate(xPos, yPos, zPos);
	graphics->RotateZ(zRot);
	graphics->Scale(xScale, yScale, zScale);
}
void Entity3D::OnCollision(Entity3D* collision) {}