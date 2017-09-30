#ifndef ENTITY2D_H
#define ENTITY2D_H
using namespace std;
#include "ImportExport.h"
#include "Entity.h"
#include "Graphics.h"

class LQN_API Entity2D : public Entity {
public:
	float width,height,collisionWidth,collisionHeight,mass;
	bool isTrigger, isKinematic;
	Entity2D(Graphics* graphics);
	virtual void Update();
	virtual void Draw();
	virtual void OnCollision(Entity2D* collision);
};


#endif