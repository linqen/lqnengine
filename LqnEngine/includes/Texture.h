#ifndef TEXTURE_H
#define TEXTURE_H
using namespace std;
#include "ImportExport.h"
#include <d3d9.h>
#include <string>

class LQN_API Texture {
public:
	int refCount=0;
	//Constructors
	Texture() {}
	Texture(wstring ptextureFileName, IDirect3DTexture9* texture) {
		textureFileName = ptextureFileName;
		//m_texture = texture;
		SetD3DTexture(texture);
	}
	//Getters and Setters
	void SetTextureFileName(wstring ptextureFileName) { textureFileName=ptextureFileName; }
	wstring GetTextureFileName() { return textureFileName; }
	IDirect3DTexture9* GetD3DTexture() { return m_texture; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	void SetD3DTexture(IDirect3DTexture9* texture)
	{
		m_texture = texture;
		if (m_texture != NULL) {
			m_texture->GetLevelDesc(0, &desc);
			height = desc.Height;
			width = desc.Width;
		}
	}
private:
	wstring textureFileName;
	IDirect3DTexture9* m_texture = 0;
	D3DSURFACE_DESC desc;
	float height, width;
};

#endif