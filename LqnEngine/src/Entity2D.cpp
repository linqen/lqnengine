#include "..\includes\Entity2D.h"
#include <timeapi.h>

Entity2D::Entity2D(Graphics *graphics):Entity(graphics){
	this->graphics = graphics;
	this->width = 10;
	this->height = 10;
	this->collisionWidth = width*2;
	this->collisionHeight = height*2;
	this->mass = 1;
	this->isKinematic = false;
	this->isTrigger = false;
}

void Entity2D::Update() {

}

void Entity2D::Draw() {
	//graphics->LoadIdentity();
	//graphics->Translate(xPos, yPos, zPos);
	//graphics->RotateZ(zRot);
	//graphics->Scale(xScale, yScale, zScale);
}
void Entity2D::OnCollision(Entity2D* collision) {}