#ifndef SCENE_H
#define SCENE_H

#include "ImportExport.h"
#include "NodeWithChildren.h"

class LQN_API Scene : public NodeWithChildren {
public:
	Transform transform;

	Scene(Graphics* graphics) :NodeWithChildren(graphics) {}

	virtual void Update() {
		NodeWithChildren::Update();
	}

	virtual void Draw() {
		D3DXMatrixIdentity(&transform);
		graphics->SetWorldTransform(&transform);
		NodeWithChildren::Draw();
	}

	//OnDraw carga set Identity
	//Graphics.setMatrix(transform)

};

#endif // !SCENE_H
