#include "..\includes\Entity3D.h"
#include <timeapi.h>

Entity3D::Entity3D(Graphics * graphics):Entity(graphics){
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
	//graphics->LoadIdentity();
	//graphics->Translate(xPos, yPos, zPos);
	//graphics->RotateX(xRot);
	//graphics->RotateY(yRot);
	//graphics->RotateZ(zRot);
	//graphics->Scale(xScale, yScale, zScale);
}
void Entity3D::OnCollision(Entity3D* collision) {}