#ifndef QUAD_H
#define QUAD_H
using namespace std;

#include "Vertex.h"
#include "Entity2D.h"

class LQN_API Quad : public Entity2D{
	Vertex *vertex;
public:
	Quad(Graphics *graphics) : Entity2D (graphics){
		vertex = new Vertex[4];
		vertex[0] = { -width, height, 0.0f, D3DCOLOR_XRGB(0, 255, 0) };
		vertex[1] = { -width, -height, 0.0f, D3DCOLOR_XRGB(0, 255, 0) };
		vertex[2] = { width, height, 0.0f, D3DCOLOR_XRGB(0, 255, 0) };
		vertex[3] = { width, -height, 0.0f, D3DCOLOR_XRGB(0, 255, 0) };

	}

	void Draw() {
		Entity2D::graphics->BindTexture(NULL);
		Entity2D::Draw();
		Entity2D::graphics->Draw2D(vertex,D3DPT_TRIANGLESTRIP,4);//Los vertices, la primitiva y la cantidad de vertices
	}
};



#endif