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
	vector<Tile*> m_tiles;
	TextureManager* textureManager;
	Texture* m_texture;
	Tile *actualTile;
public:
	TileMap(Graphics *graphics, TextureManager *ptextureManager, LPCWSTR texturePath, float tileSizeWidth, float tileSizeHeight,
		vector<vector<int>> tiles, unsigned int tilesPerWidth) : Entity2D(graphics) {
		textureManager = ptextureManager;
		m_texture = textureManager->LoadTexture(texturePath);
		for (unsigned int i = 0; i < tiles.size(); i++)
			for (unsigned int j = 0; j < tiles[i].size(); j++)
			{
				int tileNumber = tiles[i][j];
				//Use -i to create the next tile under the previous one, and not above it
				actualTile = new Tile(graphics,tileSizeWidth,tileSizeHeight,j,-i);
				actualTile->SetTexture(m_texture);
				float actualOffSetX = ((tileNumber%tilesPerWidth) * tileSizeWidth);
				float actualOffSetY = ((tileNumber / tilesPerWidth) * tileSizeHeight);
				actualTile->SetTextureZone(actualOffSetX, actualOffSetY, tileSizeWidth, tileSizeHeight);
				m_tiles.push_back(actualTile);
				actualTile->xScale = 5;
				actualTile->yScale = 5;
			}
	}
	void SetXPos(float x) {
		for (unsigned int i = 0; i < m_tiles.size(); i++) {
			m_tiles[i]->xPos = x;
		}
	}
	void SetYPos(float y) {
		for (unsigned int i = 0; i < m_tiles.size(); i++) {
			m_tiles[i]->yPos = y;
		}
	}
	void SetZPos(float z) {
		for (unsigned int i = 0; i < m_tiles.size(); i++) {
			m_tiles[i]->zPos = z;
		}
	}
	void Draw() {
		for (unsigned int i = 0; i < m_tiles.size(); i++) {
			m_tiles[i]->Draw();
		}
	}
	void Update() {}
	void OnCollision(Entity2D*collision) {}
};
#endif