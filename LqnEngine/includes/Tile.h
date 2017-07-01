#ifndef TILE_H
#define TILE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <string>
#include "Time.h"
#include "SpriteAnimation.h"

class LQN_API Tile : public Entity2D {
private:
	VertexUV *vertex;
	TextureManager* textureManager;
	Texture* m_texture;
	SpriteAnimation* m_spriteAnimation = NULL;
	int actualFrame;
	float actualOffSetX;
	float actualOffSetY;
	float m_tileWidth;
	float m_tileHeight;
	float timer = 0;
	bool isAnimation = false;
public:
	Tile(Graphics *graphics) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { -width, height, 0.5f, 0.0f, 0.0f };
		vertex[1] = { -width, -height, 0.5f, 0.0f, 1.0f };
		vertex[2] = { width, height, 0.5f, 1.0f, 0.0f };
		vertex[3] = { width, -height, 0.5f, 1.0f, 1.0f };
	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4);
	}
	void Update() {
		Entity2D::Update();
	}
	void SetTexture(Texture* texture) {
		m_texture = texture;
	}
};

#endif