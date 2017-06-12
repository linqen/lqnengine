#ifndef SPRITE_H
#define SPRITE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <string>
#include "Time.h"

class LQN_API Sprite : public Entity2D {
private:
	VertexUV *vertex;
	TextureManager* textureManager;
	Texture* m_texture;
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
	Sprite(Graphics *graphics,TextureManager *ptextureManager) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { -200.0f, 200.0f, 0.5f, 0.0f, 0.0f };
		vertex[1] = { -200.0f, -200.0f, 0.5f, 0.0f, 1.0f };
		vertex[2] = { 200.0f, 200.0f, 0.5f, 1.0f, 0.0f };
		vertex[3] = { 200.0f, -200.0f, 0.5f, 1.0f, 1.0f };
		textureManager = ptextureManager;
	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4);
	}
	void SetTexture(LPCWSTR texturePath) {
		m_texture = textureManager->LoadTexture(texturePath);
	}
	void SetTextureZone(float offSetX,float offSetY,float tileWidth,float tileHeight) {
		vertex[0].setUV(offSetX/ m_texture->GetWidth(), offSetY/ m_texture->GetHeight());
		vertex[1].setUV(offSetX/ m_texture->GetWidth(), (offSetY+ tileHeight)/ m_texture->GetHeight());
		vertex[2].setUV((offSetX+ tileWidth)/ m_texture->GetWidth(), offSetY/ m_texture->GetHeight());
		vertex[3].setUV((offSetX+ tileWidth)/ m_texture->GetWidth(), (offSetY+ tileHeight)/ m_texture->GetHeight());
	}
	void Update() {
		Entity2D::Update();
		//This is to animate, using a clock
		if (isAnimation) {
			timer += Time::deltaTime;
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
	//Unload the texture
	void UnloadTexture() {
		textureManager->Unload(m_texture);
		StopAnimation();
		m_texture = NULL;
	}
private:
	//Go to the next tile based on Offsets, width and height
	void Animate() {
		actualOffSetX += m_tileWidth;
		if (actualOffSetX == m_texture->GetWidth()) {
			actualOffSetY += m_tileHeight;
			if (actualOffSetY == m_texture->GetHeight()) {
				actualOffSetY = 0;
			}
			actualOffSetX = 0;
		}
		SetTextureZone(actualOffSetX, actualOffSetY, m_tileWidth, m_tileHeight);
	}
};

#endif