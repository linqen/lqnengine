#ifndef SPRITE_H
#define SPRITE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <string>
#include "Time.h"
#include "SpriteAnimation.h"

class LQN_API Sprite : public Entity2D {
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
	Sprite(Graphics *graphics,TextureManager *ptextureManager) : Entity2D(graphics) {
		vertex = new VertexUV[4];
		vertex[0] = { -width, height, 0.5f, 0.0f, 0.0f };
		vertex[1] = { -width, -height, 0.5f, 0.0f, 1.0f };
		vertex[2] = { width, height, 0.5f, 1.0f, 0.0f };
		vertex[3] = { width, -height, 0.5f, 1.0f, 1.0f };
		textureManager = ptextureManager;
	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4);
	}
	void Update() {
		Entity2D::Update();
		//This is to animate, using a clock
		if (isAnimation) {
			timer += Time::deltaTime;
			if (timer >= m_spriteAnimation->manimTime) {
				Animate();
				timer = 0.0f;
			}
		}
	}

	void OnCollision(Entity2D*collision) {
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

	//Set and start the animation
	void SetAnimation(SpriteAnimation* spriteAnimation) {
		m_spriteAnimation = spriteAnimation;
		actualOffSetX= m_spriteAnimation->moffSetX;
		actualOffSetY= m_spriteAnimation->moffSetY;
		actualFrame=0;
		SetFrame(actualFrame);
		isAnimation = true;
	}

	//Start animation
	void StartAnimation() {
		if(m_spriteAnimation!=NULL)
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
		delete m_spriteAnimation;
		m_spriteAnimation = NULL;
		m_texture = NULL;
	}
private:
	void Animate() {
		actualFrame++;
		if (actualFrame >= m_spriteAnimation->mtotalFrames)
			actualFrame = 0;
		SetFrame(actualFrame);
	}
	void SetFrame(int frame) {
		//Move the offset to the position based on frame
		actualOffSetX = m_spriteAnimation->moffSetX + ((frame%m_spriteAnimation->mframesbyWidth) * m_spriteAnimation->mframeWidth);
		actualOffSetY = m_spriteAnimation->moffSetY + ((frame / m_spriteAnimation->mframesbyWidth) * m_spriteAnimation->mframeHeight);
		//Set the new texture zone
		SetTextureZone(actualOffSetX, actualOffSetY, m_spriteAnimation->mframeWidth, m_spriteAnimation->mframeHeight);
	}
};

#endif