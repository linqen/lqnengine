#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ImportExport.h"
#include "NodeWithChildren.h"
class LQN_API GameObject : public NodeWithChildren {
public:
	
	GameObject(Graphics * graphics) :NodeWithChildren(graphics) {};

	virtual void Update() {
		NodeWithChildren::Update();
	}

	virtual void Draw() {
		//Pushea en una pila la matriz actual 
		graphics->PushCurrentlMatrix();
		graphics->Translate(xPos, yPos, zPos);
		graphics->RotateX(xRot);
		graphics->RotateY(yRot);
		graphics->RotateZ(zRot);
		graphics->Scale(xScale, yScale, zScale);
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Draw();
		}
		NodeWithChildren::Draw();

		//Saca la ultima y setea la que quede como ultima
		graphics->PopLastMatrix();
	}

	void AddComponent(Node* newComponent) {
		newComponent->SetParent(this);
		components.push_back(newComponent);
	}

	bool RemoveComponent(Node* componentToRemove) { return true; }

protected:
	Transform transform;
private:
	vector<Node*> components;
};

#endif // !GAMEOBJECT_H
