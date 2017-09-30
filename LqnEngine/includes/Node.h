#ifndef NODE_H
#define NODE_H
using namespace std;
#include "ImportExport.h"
#include "Graphics.h"
class LQN_API Node {
public:
	Node(Graphics * graphics) {
		this->graphics = graphics;
	}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void SetParent(Node* node) {}
protected:
	Graphics * graphics;
	Node* parent;
};

#endif