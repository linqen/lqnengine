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
		lastXPos = xPos = 0;
		lastYPos = yPos = 0;
		lastZPos = zPos = 0;
		lastXRot = xRot = 0;
		lastYRot = yRot = 0;
		lastZRot = zRot = 0;
		lastXScale = xScale = 1;
		lastYScale = yScale = 1;
		lastZScale = zScale = 1;
	}
	~NodeWithChildren() {}

	virtual void Update() {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Update();
		}
		Node::Update();
	}
	virtual void Draw(D3DXPLANE* frustumPlane, D3DXVECTOR3* minFrustumBoxBounds, D3DXVECTOR3* maxFrustumBoxBounds) {
		for (size_t i = 0; i < childrens.size(); i++)
		{
			childrens[i]->Draw(frustumPlane, minFrustumBoxBounds, maxFrustumBoxBounds);

		}
		Node::Draw();

	}

	void AddChildren(NodeWithChildren* newNode) {
		newNode->SetParent(this);
		childrens.push_back(newNode);
	}

	bool RemoveChildren(NodeWithChildren* nodeToRemove) { return true; }

protected:
	float lastXPos, lastYPos, lastZPos, lastXRot, lastYRot, lastZRot, lastXScale, lastYScale, lastZScale;
	Transform * transform;
	vector<NodeWithChildren*> childrens;
};


#endif