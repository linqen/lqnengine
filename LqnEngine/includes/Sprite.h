#ifndef SPRITE_H
#define SPRITE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"

class LQN_API Sprite : public Entity2D {
	//Vertex * vertex
	VertexUV *vertex;/* [] =
					 {
					 { 120.0f, 400.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
					 { 120.0f, 50.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
					 { 520.0f, 400.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
					 { 520.0f, 50.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0)},
					 };*/
public:
	//Sprite();
	Sprite(Graphics *graphics) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { 120.0f, 400.0f, 0.5f, 0.0f, 1.0f };
		vertex[1] = { 120.0f, 50.0f, 0.5f, 0.0f, 0.0f };
		vertex[2] = { 520.0f, 400.0f, 0.5f, 1.0f, 1.0f };
		vertex[3] = { 520.0f, 50.0f, 0.5f, 1.0f, 0.0f };

	}

	//VertexUV vertices[] =
	//{
	//	{ 120.0f, 400.0f, 0.5f, 0.0f, 1.0f },
	//	{ 120.0f, 50.0f, 0.5f, 0.0f, 0.0f },
	//	{ 520.0f, 400.0f, 0.5f, 1.0f, 1.0f },
	//	{ 520.0f, 50.0f, 0.5f, 1.0f, 0.0f },
	//};

	void Draw() {
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4);//Los vertices, la primitiva y la cantidad de vertices
	}
};



#endif