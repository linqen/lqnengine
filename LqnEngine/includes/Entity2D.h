#ifndef ENTITY2D_H
#define ENTITY2D_H
using namespace std;
#include "ImportExport.h"
#include "Entity.h"
#include "Graphics.h"

class LQN_API Entity2D : public Entity {
public:
	float xPos, yPos, zPos, zRot, xScale, yScale, zScale;
	Graphics * graphics;
	Entity2D(Graphics *graphics);
	virtual void Update();
	virtual void Draw();
};


#endif