#ifndef SPRITE_H
#define SPRITE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include <string>

class LQN_API Sprite : public Entity2D {
	VertexUV *vertex;
	string texturePath;
	IDirect3DTexture9* m_texture = 0;
public:
	Sprite(Graphics *graphics) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { 120.0f, 400.0f, 0.5f, 0.0f, 0.0f };
		vertex[1] = { 120.0f, 50.0f, 0.5f, 0.0f, 1.0f };
		vertex[2] = { 520.0f, 400.0f, 0.5f, 1.0f, 0.0f };
		vertex[3] = { 520.0f, 50.0f, 0.5f, 1.0f, 1.0f };

	}

	void Draw() {
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4, m_texture);
	}
	void setTexture(string texturePath) {
		wstring stemp = wstring(texturePath.begin(), texturePath.end());
		LPCWSTR sw = stemp.c_str();
		D3DXCreateTextureFromFile(graphics->pd3dDevice, sw, &m_texture);
	}
};



#endif