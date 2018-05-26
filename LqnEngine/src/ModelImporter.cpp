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

bool ModelImporter::importScene(const std::string& rkFilename, GameObject& orkSceneRoot,vector<BSPPlane*>* out_BSP_Plane) {

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
		importNode(iRoot->mChildren[i], orkSceneRoot, scene, out_BSP_Plane);
	}
	if (out_BSP_Plane != NULL && !out_BSP_Plane->empty()) {
		orkSceneRoot.SetBSPPlanes(*out_BSP_Plane);
	}
	return true;
}

void ModelImporter::importNode(aiNode* child, GameObject& parent, const aiScene* scene, vector<BSPPlane*>* out_BSP_Plane) {

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
			importNode(child->mChildren[k], *newNode, scene, out_BSP_Plane);
		}
	}
	const aiMesh* rootMesh;
	for (unsigned int l = 0; l < child->mNumMeshes; l++) {

		rootMesh = scene->mMeshes[child->mMeshes[l]];

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

	if (out_BSP_Plane!=NULL && newNode->GetName().length()>2 && newNode->GetName().find("BSP")!=string::npos) {
		int i = 0;
		out_BSP_Plane->push_back(new BSPPlane());
		D3DXVECTOR3 planePos[BSPPlane::AmountOfVertices];

		//D3DXMATRIX matrizPrueba = D3DXMATRIX(10, -8.74e-07f, -8.74e-07f, 0, -8.74e-07f, -10, -8.74e-07f, 0, -8.74e-07f, 8.74e-07f, -10, 0, 0, 0, 0, 1);

		for (unsigned int i = 0; i < BSPPlane::AmountOfVertices; i++) {
			planePos[i] = D3DXVECTOR3(rootMesh->mVertices[i].x, rootMesh->mVertices[i].y, rootMesh->mVertices[i].z);
			//D3DXVec3TransformCoord(&planePos[i], &planePos[i], &matrizPrueba);
		}
		D3DXPLANE plane;
		D3DXPlaneFromPoints(&plane, &planePos[0], &planePos[1], &planePos[2]);
		out_BSP_Plane->back()->SetPlane(plane);
		out_BSP_Plane->back()->SetVertices(planePos);
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