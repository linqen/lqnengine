#ifndef SPRITE_H
#define SPRITE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include <string>

class LQN_API Sprite : public Entity2D {
private:
	VertexUV *vertex;
	string texturePath;
	IDirect3DTexture9* m_texture = 0;
	D3DSURFACE_DESC desc;
	float m_offSetX;
	float m_offSetY;
	float actualOffSetX;
	float actualOffSetY;
	float m_tileWidth;
	float m_tileHeight;
	float timer = 0;
	float m_animTime = 0;
	bool isAnimation = false;
public:
	Sprite(Graphics *graphics) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { -200.0f, 200.0f, 0.5f, 0.0f, 0.0f };
		vertex[1] = { -200.0f, -200.0f, 0.5f, 0.0f, 1.0f };
		vertex[2] = { 200.0f, 200.0f, 0.5f, 1.0f, 0.0f };
		vertex[3] = { 200.0f, -200.0f, 0.5f, 1.0f, 1.0f };
	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4, m_texture);
	}
	void SetTexture(LPCWSTR texturePath) {
		m_texture = graphics->LoadTexture(texturePath);
		m_texture->GetLevelDesc(0, &desc);
	}
	void SetTextureZone(float offSetX,float offSetY,float tileWidth,float tileHeight) {
		vertex[0].setUV(offSetX/desc.Width, offSetY/desc.Height);
		vertex[1].setUV(offSetX/desc.Width, (offSetY+ tileHeight)/desc.Height);
		vertex[2].setUV((offSetX+ tileWidth)/desc.Width, offSetY/desc.Height);
		vertex[3].setUV((offSetX+ tileWidth)/desc.Width, (offSetY+ tileHeight)/desc.Height);
	}
	void Update() {
		Entity2D::Update();
		//This is to animate, using a clock
		if (isAnimation) {
			timer += 1.0f;
			if (timer >= m_animTime) {
				Animate();
				timer = 0.0f;
			}
		}

	}
	//Start animation, time based on seconds
	void SetAnimation(float offSetX, float offSetY, float tileWidth, float tileHeight, float animTime) {
		SetTextureZone(offSetX, offSetY, tileWidth, tileHeight);
		m_offSetX = offSetX;
		actualOffSetX = offSetX;
		m_offSetY = offSetY;
		actualOffSetY = offSetY;
		m_tileWidth = tileWidth;
		m_tileHeight = tileHeight;
		m_animTime = animTime;
		isAnimation = true;
	}
	//Stop animation
	void StopAnimation() {
		isAnimation = false;
	}
private:
	//Go to the next tile based on Offsets, width and height
	void Animate() {
		actualOffSetX += m_tileWidth;
		if (actualOffSetX == desc.Width) {
			actualOffSetY += m_tileHeight;
			if (actualOffSetY == desc.Height) {
				actualOffSetY = 0;
			}
			actualOffSetX = 0;
		}
		SetTextureZone(actualOffSetX, actualOffSetY, m_tileWidth, m_tileHeight);
	}
};

#endif