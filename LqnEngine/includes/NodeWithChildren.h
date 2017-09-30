#ifndef NODEWITHCHILDREN_H
#define NODEWITHCHILDREN_H

#include "ImportExport.h"
#include <vector>
#include "Node.h"
typedef D3DXMATRIX Transform;
class LQN_API NodeWithChildren : public Node {
public:
	float xPos, yPos, zPos, xRot, yRot, zRot, xScale, yScale, zScale;
	NodeWithChildren(Graphics *graphics) : Node (graphics) {
		this->xPos = 0;
		this->yPos = 0;
		this->zPos = 0;
		this->xRot = 0;
		this->yRot = 0;
		this->zRot = 0;
		this->xScale = 1;
		this->yScale = 1;
		this->zScale = 1;
	}
	~NodeWithChildren() {}

	virtual void Update() {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Update();
		}
		Node::Update();
	}
	virtual void Draw() {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Draw();

		}
		Node::Draw();

	}

	void AddChildren(NodeWithChildren* newNode) {
		childrens.push_back(newNode);
	}

	bool RemoveChildren(NodeWithChildren* nodeToRemove) { return true; }

protected:
	Transform * transform;
private:
	vector<Node*> childrens;
};


#endif