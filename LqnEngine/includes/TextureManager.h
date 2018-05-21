#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
using namespace std;
#include <string>
#include "ImportExport.h"
#include "Graphics.h"
#include "Texture.h"
#include <vector>

class LQN_API Graphics;

class LQN_API TextureManager {
private:
	const wstring TEXTURESFOLDER = L"..\\Textures\\";
	vector<Texture*> textures;
	Graphics* graphics;
public:
	bool Create(Graphics* pgraphics) {
		graphics = pgraphics;
		if (graphics != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	Texture* LoadTexture(wstring textureFileName) {
		wstring fileName = TEXTURESFOLDER;
		fileName.append(textureFileName.c_str());
		LPCWSTR fullPath = fileName.c_str();
		if (textures.empty()) {
			Texture* texture = new Texture(textureFileName, graphics->LoadTexture(fullPath));
			texture->refCount++;
			textures.push_back(texture);
			return texture;
		}
		for (size_t i = 0; i < textures.size(); i++)
		{

			if (textures[i]->GetTextureFileName() == textureFileName) {
				textures[i]->refCount++;
				return textures[i];
			}
			else {
				Texture* texture = new Texture(textureFileName, graphics->LoadTexture(fullPath));
				texture->refCount++;
				textures.push_back(texture);
				return texture;
			}
		}
	}

	Texture* LoadTexture(string stextureFileName) {
		wstring textureFileName = s2ws(stextureFileName);
		wstring fileName = TEXTURESFOLDER;
		fileName.append(textureFileName.c_str());
		LPCWSTR fullPath = fileName.c_str();
		if (textures.empty()) {
			Texture* texture = new Texture(textureFileName, graphics->LoadTexture(fullPath));
			texture->refCount++;
			textures.push_back(texture);
			return texture;
		}
		for (size_t i = 0; i < textures.size(); i++)
		{

			if (textures[i]->GetTextureFileName() == textureFileName) {
				textures[i]->refCount++;
				return textures[i];
			}
		}
		Texture* texture = new Texture(textureFileName, graphics->LoadTexture(fullPath));
		texture->refCount++;
		textures.push_back(texture);
		return texture;
	}

	//Remove the texture from the VGA
	void Unload(Texture* textureToUnload) {
		if (textureToUnload == NULL) {
			return;
		}
		textureToUnload->refCount--;
		if (textureToUnload->refCount <= 0) {
			graphics->ReleaseTexture(textureToUnload);
			for (size_t i = 0; i < textures.size(); i++)
			{
				if (textures[i] == textureToUnload) {
					textures.erase(textures.begin()+i);
				}
			}
			delete textureToUnload;
		}
	}

private:
	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
};

#endif