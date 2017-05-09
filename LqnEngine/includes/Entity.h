#ifndef ENTITY_H
#define ENTITY_H
using namespace std;
#include "ImportExport.h"
#include <string>

class LQN_API Entity {
public:
	void SetName(string pname) { name = pname; }
	string GetName() { return name; }
protected:
	virtual void Update() {};
	virtual void Draw() {};
private:
	string name;
};


#endif