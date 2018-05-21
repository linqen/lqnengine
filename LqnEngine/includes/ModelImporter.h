#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H
#include "ImportExport.h"
#include "Mesh.h"
#include "Graphics.h"
#include "TextureManager.h"
struct aiNode;
struct aiScene;

struct aiMesh;
struct aiMaterial;

class LQN_API ModelImporter {


public:
	//ModelImporter();
	bool Initialize(Graphics* graphics, TextureManager* textureManager);
	//~ModelImporter();
	bool importScene(const std::string& rkFilename, GameObject& orkSceneRoot);

private:
	void importNode(aiNode* child, GameObject& parent, const aiScene* scene);

	//vector <Texture*> m_Textures;
	Graphics* importGraphics;
	TextureManager* textureManager;

};
#endif