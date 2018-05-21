#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "ImportExport.h"
#include "GameObject.h"

class LQN_API Component{
public:
	GameObject * gameObject;
	Component(Graphics *graphics){
		this->graphics = graphics;
	}
	~Component() {}

	virtual void Update() {}
	virtual void Draw() {}
	virtual void CalculateBounds() {}

	virtual void SetParent(NodeWithChildren * nodeWithChildren){
		gameObject = (GameObject*)nodeWithChildren;
	}
protected:
	Graphics * graphics;
};


#endif