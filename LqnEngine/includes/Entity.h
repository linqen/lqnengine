#ifndef ENTITY_H
#define ENTITY_H
using namespace std;
#include "ImportExport.h"
#include <string>
#include "Component.h"

class LQN_API Entity : public Component {
public:
	void SetName(string pname) { name = pname; }
	string GetName() { return name; }
	Entity(Graphics* graphics):Component(graphics) {}
protected:
	virtual void Update() {};
	virtual void Draw() {};
private:
	string name;
};


#endif