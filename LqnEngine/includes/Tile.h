#ifndef TILE_H
#define TILE_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <string>
#include "Time.h"
#include "SpriteAnimation.h"
#include <exception>
class LQN_API Tile : public Entity2D {
private:
	VertexUV *vertex;
	Texture* m_texture;
public:
	Tile() {}
	Tile(Graphics *graphics,float tileWidth,float tileHeight,int positionX,int positionY) : Entity2D(graphics) {
		vertex = new (nothrow) VertexUV[4];
		width = tileWidth;
		height = tileHeight;
		vertex[0] = { (positionX*width), (positionY+1)*height, 0.5f, 0.0f, 0.0f };
		vertex[1] = { (positionX*width), (positionY*height), 0.5f, 0.0f, 1.0f };
		vertex[2] = { (positionX+1)*width, (positionY + 1)*height, 0.5f, 1.0f, 0.0f };
		vertex[3] = { (positionX + 1)*width, (positionY*height), 0.5f, 1.0f, 1.0f };
	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, 4);
	}
	void Update() {
		Entity2D::Update();
	}
	void OnCollision(Entity2D*collision) {}
	void SetTexture(Texture* texture) {
		m_texture = texture;
	}
	void SetTextureZone(float offSetX, float offSetY, float tileWidth, float tileHeight) {
		vertex[0].setUV(offSetX / m_texture->GetWidth(), offSetY / m_texture->GetHeight());
		vertex[1].setUV(offSetX / m_texture->GetWidth(), (offSetY + tileHeight) / m_texture->GetHeight());
		vertex[2].setUV((offSetX + tileWidth) / m_texture->GetWidth(), offSetY / m_texture->GetHeight());
		vertex[3].setUV((offSetX + tileWidth) / m_texture->GetWidth(), (offSetY + tileHeight) / m_texture->GetHeight());
	}
};

#endif