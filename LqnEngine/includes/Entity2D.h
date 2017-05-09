#ifndef ENTITY2D_H
#define ENTITY2D_H
using namespace std;
#include "ImportExport.h"
#include "Entity.h"

class LQN_API Entity2D : public Entity {
public:
	float xPos, yPos, zPos, xRot, yRot, zRot, xScale, yScale, zScale;
	void Update() ;
	void Draw();
};


#endif