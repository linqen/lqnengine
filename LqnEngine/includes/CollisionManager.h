#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "ImportExport.h"
#include "Entity2D.h"
#include <vector>
class LQN_API CollisionManager {
public:
	double deltaTime;
	bool Initialize();
	void AddCollisionable(Entity2D* entity,int layer);
	void CheckCollision();
	void RemoveCollisionable(Entity2D* entity,int layer);
private:
	void MoveOnCollision(Entity2D* ent1, Entity2D* ent2,float px,float py);
	void MoveOnCollisionX(Entity2D* entity, float movement);
	void MoveOnCollisionY(Entity2D* entity, float movement);
	vector<Entity2D*> layer1;
	vector<Entity2D*> layer2;
};
#endif

