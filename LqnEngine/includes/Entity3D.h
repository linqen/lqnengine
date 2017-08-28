#ifndef ENTITY3D_H
#define ENTITY3D_H
using namespace std;
#include "ImportExport.h"
#include "Entity.h"
#include "Graphics.h"

class LQN_API Entity3D : public Entity {
public:
	float xPos, yPos, zPos, xRot, yRot, zRot, xScale, yScale, zScale, width, height, collisionWidth, collisionHeight, mass;
	bool isTrigger, isKinematic;
	Graphics * graphics;
	Entity3D() {}
	Entity3D(Graphics *graphics);
	virtual void Update();
	virtual void Draw();
	virtual void OnCollision(Entity3D* collision);
};


#endif