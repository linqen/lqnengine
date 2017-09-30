#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "ImportExport.h"
#include "GameObject.h"

class LQN_API Component : public Node {
public:
	GameObject * gameObject;
	Component(Graphics *graphics) : Node(graphics) {}
	~Component() {}

	virtual void Update() {
		Node::Update();
	}
	virtual void Draw() {
		Node::Draw();
	}
	virtual void SetParent(Node * node){
		gameObject = (GameObject*)node;
	}
};


#endif