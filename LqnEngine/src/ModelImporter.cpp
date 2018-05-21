#include "..\includes\ModelImporter.h"

#include <assimp\Importer.hpp>      // C++ importer interface
#include <assimp\scene.h>			// Output data structure
#include <assimp\postprocess.h>     // Post processing fla
#include <assert.h>


bool ModelImporter::Initialize(Graphics* graphics, TextureManager* r_textureManager) {
	importGraphics = graphics;
	textureManager = r_textureManager;
	return true;
}

bool ModelImporter::importScene(const std::string& rkFilename, GameObject& orkSceneRoot) {

	Assimp::Importer importer;

	aiString* path = new aiString;
	path->Set(rkFilename);

	const aiScene* scene = importer.ReadFile(rkFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
		return false;

	if (!scene->HasMeshes())
		return false;

	aiNode* iRoot = scene->mRootNode;

	if (iRoot->mNumChildren <= 0 && iRoot->mNumMeshes <= 0)
		return false;

	aiVector3t<float> positionRoot;
	aiQuaterniont<float> rotationRoot;
	aiVector3t<float> scaleRoot;
	iRoot->mTransformation.Decompose(scaleRoot, rotationRoot, positionRoot);
	orkSceneRoot.SetPosition(positionRoot.x, positionRoot.y, positionRoot.z);
	orkSceneRoot.SetRotation(rotationRoot.x, rotationRoot.y, rotationRoot.z);
	orkSceneRoot.SetScale(scaleRoot.x, scaleRoot.y, scaleRoot.z);
	orkSceneRoot.SetName(iRoot->mName.C_Str());

	for (unsigned int i = 0; i < iRoot->mNumChildren; i++) {
		importNode(iRoot->mChildren[i], orkSceneRoot, scene);
	}

	return true;
}

void ModelImporter::importNode(aiNode* child, GameObject& parent, const aiScene* scene) {

	aiVector3t<float> position;
	aiQuaterniont<float> rotation;
	aiVector3t<float> scale;
	child->mTransformation.Decompose(scale, rotation, position);
	GameObject* newNode = new GameObject(importGraphics);
	newNode->SetPosition(position.x, position.y, position.z);
	newNode->SetRotation(rotation.x, rotation.y, rotation.z);
	newNode->SetScale(scale.x, scale.y, scale.z);
	newNode->SetName(child->mName.C_Str());

	if (child->mNumChildren != 0) {
		for (unsigned int k = 0; k < child->mNumChildren; k++) {
			importNode(child->mChildren[k], *newNode, scene);
		}
	}

	for (unsigned int l = 0; l < child->mNumMeshes; l++) {

		const aiMesh* rootMesh = scene->mMeshes[child->mMeshes[l]];

		vector<VertexUV> vertices;

		for (unsigned int i = 0; i < rootMesh->mNumVertices; i++) {
			VertexUV newVertex;
			newVertex.setCoordinates(rootMesh->mVertices[i].x,
				rootMesh->mVertices[i].y,
				rootMesh->mVertices[i].z);
			if (rootMesh->mTextureCoords[0] != NULL) {
				newVertex.setUV(rootMesh->mTextureCoords[0][i].x,
					rootMesh->mTextureCoords[0][i].y);
			}
			if (rootMesh->mNormals != NULL) {
				newVertex.setNormals(rootMesh->mNormals[i].x,
					rootMesh->mNormals[i].y,
					rootMesh->mNormals[i].z);
			}
			vertices.push_back(newVertex);
		}

		vector<short> indices;

		for (unsigned int j = 0; j < rootMesh->mNumFaces; j++) {
			const aiFace& meshFace = rootMesh->mFaces[j];
			//Mesh faces needs to have 3 edges. If have 4, the program close
			assert(meshFace.mNumIndices == 3);

			for (int k = 0; k < 3; k++) {
				indices.push_back(meshFace.mIndices[k]);
			}
		}
		Mesh* newMesh = new Mesh(importGraphics, textureManager, vertices, indices);
		if (scene->HasMaterials()) {

			const aiMaterial* material = scene->mMaterials[rootMesh->mMaterialIndex];
			aiString texturePath;

			material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

			string actualPath = texturePath.C_Str();

			Texture* texture = textureManager->LoadTexture(actualPath);


			newMesh->SetTexture(texture);
		}

		//GameObject* newMeshGo = new GameObject(importGraphics);
		//newMeshGo->SetPosition(position.x, position.y, position.z);
		//newMeshGo->SetRotation(rotation.x, rotation.y, rotation.z);
		//newMeshGo->SetScale(scale.x, scale.y, scale.z);
		//
		//newMeshGo->SetName(child->mName.C_Str());

		newNode->AddComponent(newMesh);
	}
	parent.AddChildren(newNode);
}