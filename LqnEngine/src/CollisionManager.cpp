#include "../includes/CollisionManager.h"

bool CollisionManager::Initialize() {
	if (this == NULL)
		return false;
	return true;
 }

void CollisionManager::AddCollisionable(Entity2D* entity,int layer){
	switch (layer)
	{
	case 1:layer1.push_back(entity);
		break;
	case 2:layer2.push_back(entity);
		break;
	default:return;
	}

}

void CollisionManager::CheckCollision() {
	Entity2D* ent1;
	Entity2D* ent2;
	float x1, y1;
	float x2, y2;
	float dx, dy;
	float px, py;
	for (size_t i = 0; i < layer1.size(); i++)
	{
		ent1 = layer1[i];
		x1 = ent1->xPos;
		y1 = ent1->yPos;
		for (size_t j = 0; j < layer2.size(); j++)
		{
			ent2 = layer2[j];
			x2 = ent2->xPos;
			y2 = ent2->yPos;
			//use abs for absolute values (Not negatives)
			dx = abs(x2 - x1);
			dy = abs(y2 - y1);
			if (dx < ((ent1->collisionWidth + ent2->collisionWidth) / 2) &&
				dy < ((ent1->collisionHeight + ent2->collisionHeight) / 2) &&
				!ent1->isTrigger && !ent2->isTrigger) {

				px = (ent1->collisionWidth + ent2->collisionWidth) / 2 - dx;
				py = (ent1->collisionHeight + ent2->collisionHeight) / 2 - dy;

				//ent on collision llamando solo a entity2d oncollision
				//por mal funcionamiento
				layer1[i]->OnCollision(ent2);
				layer2[j]->OnCollision(ent1);
				MoveOnCollision(ent1, ent2, px, py);
			}
		}
	} 
}

void CollisionManager::MoveOnCollision(Entity2D* ent1, Entity2D* ent2,float px, float py) {
	float totalMass, mass1, mass2;
	totalMass = ent1->mass + ent2->mass;
	mass1 = ent1->mass / totalMass;
	mass2 = ent2->mass / totalMass;

	if (px < py) {
		//horizontal
		if (ent1->xPos < ent2->xPos) {
			MoveOnCollisionX(ent1, -px*mass1);
			MoveOnCollisionX(ent2, px*mass2);
		}
		else {
			MoveOnCollisionX(ent1, px*mass1);
			MoveOnCollisionX(ent2, -px*mass2);
		}
	}
	else {
		//vertical
		if (ent1->yPos < ent2->yPos) {
			MoveOnCollisionY(ent1, -py*mass1);
			MoveOnCollisionY(ent2, py*mass2);
		}
		else {
			MoveOnCollisionY(ent1, py*mass1);
			MoveOnCollisionY(ent2, -py*mass2);
		}
	}
}
void CollisionManager::MoveOnCollisionX(Entity2D* entity, float movement) {
	if (!entity->isKinematic) {
		entity->xPos += movement;
	}
}
void CollisionManager::MoveOnCollisionY(Entity2D* entity, float movement) {
	if (!entity->isKinematic) {
		entity->yPos += movement;
	}
}



void CollisionManager::RemoveCollisionable(Entity2D* entity, int layer) {

	switch (layer)
	{
	case 1:
		for (size_t i = 0; i < layer1.size(); i++)
		{
			if (layer1[i] == entity) {
				layer1.erase(layer1.begin() + i);
			}
		}
		break;
	case 2:
		for (size_t i = 0; i < layer2.size(); i++)
		{
			if (layer2[i] == entity) {
				layer2.erase(layer2.begin() + i);
			}
		}
		break;
	default:return;
	}

}