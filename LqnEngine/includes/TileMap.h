#ifndef TILEMAP_H
#define TILEMAP_H
using namespace std;

#include "VertexUV.h"
#include "Entity2D.h"
#include "TextureManager.h"
#include <string>
#include "Time.h"
#include "SpriteAnimation.h"
#include "Tile.h"
#include <vector>
class LQN_API TileMap : public Entity2D {
private:
	VertexUV *vertex;
	vector<Tile*> m_tiles;
	TextureManager* textureManager;
	Texture* m_texture;
	SpriteAnimation* m_spriteAnimation = NULL;
	int actualFrame;
	float actualOffSetX;
	float actualOffSetY;
	float m_tileWidth;
	float m_tileHeight;
	float timer = 0;
	int vertexCount = 0;
	bool isAnimation = false;
public:
	TileMap(Graphics *graphics, TextureManager *ptextureManager, LPCWSTR texturePath, float tileSizeWidth, float tileSizeHeight,
		const int* tiles, unsigned int width, unsigned int height) : Entity2D(graphics) {
		vertexCount = width * height * 4;
		vertex = new VertexUV[vertexCount];

		textureManager = ptextureManager;
		m_texture = textureManager->LoadTexture(texturePath);
		//vertex[0] = { -width, height, 0.5f, 0.0f, 0.0f };
		//vertex[1] = { -width, -height, 0.5f, 0.0f, 1.0f };
		//vertex[2] = { width, height, 0.5f, 1.0f, 0.0f };
		//vertex[3] = { width, -height, 0.5f, 1.0f, 1.0f };

		for (unsigned int i = 0; i < width; i++)
			for (unsigned int j = 0; j < height; j++)
			{
				// get the current tile number
				int tileNumber = tiles[i + j * width];

				// find its position in the tileset texture
				int tu = tileNumber % ((int)m_texture->GetWidth() / (int)tileSizeWidth);
				int tv = tileNumber / ((int)m_texture->GetWidth() / (int)tileSizeWidth);

				// get a pointer to the current tile's quad
				//sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
				vertex[((i + j * width) * 4)] = { -(i*tileSizeWidth), (j + 1) * tileSizeHeight, 0.5f, tu * tileSizeWidth, tv * tileSizeHeight };
				vertex[((i + j * width) * 4)+1] = { -(i*tileSizeWidth), -(j*tileSizeHeight), 0.5f, tu * tileSizeWidth, (tv+1) * tileSizeHeight };
				vertex[((i + j * width) * 4)+2] = { (i+1)*tileSizeWidth, (j + 1) * tileSizeHeight, 0.5f, (tu+1) * tileSizeWidth, tv * tileSizeHeight };
				vertex[((i + j * width) * 4)+3] = { (i+1)*tileSizeWidth, -(j*tileSizeHeight), 0.5f, (tu+1) * tileSizeWidth, (tv+1) * tileSizeHeight };
			}

	}
	void Draw() {
		Entity2D::graphics->BindTexture(m_texture);
		Entity2D::Draw();
		Entity2D::graphics->DrawSprite(vertex, D3DPT_TRIANGLESTRIP, vertexCount);
	}
	void Update() {
	}

	void OnCollision(Entity2D*collision) {}

};
#endif