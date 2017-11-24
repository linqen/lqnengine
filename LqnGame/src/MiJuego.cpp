#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	camera = new Camera(&graphics, 60, 0.1f, 1000.0f);
	cameraMov = new CameraMovement(&graphics, camera, &input, 1000);
	camera->AddComponent(cameraMov);
	camera->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));

	goMesh = new GameObject(&graphics);
	camera->AddChildren(goMesh);
	mesh = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	mesh->SetDebugMode(true);
	mesh->SetTexture(L"13.jpg");
	//goMesh->zPos = 40;
	//goMesh->yPos = -40;
	//goMesh->xPos = 50;
	//goMesh->yRot = 3.14;
	goMesh->AddComponent(mesh);



	//goMesh2 = new GameObject(&graphics);
	//camera->AddChildren(goMesh2);
	//mesh2 = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	////mesh2->SetDebugMode(true);
	//mesh2->SetTexture(L"13.jpg");
	//goMesh2->zPos = -40;
	//goMesh2->yPos = 40;
	//goMesh2->xPos = -50;
	//goMesh2->yRot = 3.14;
	//goMesh2->AddComponent(mesh2);

	//goQuad = new GameObject(&graphics);
	//camera->AddChildren(goQuad);
	//Quad * quad = new Quad(&graphics);
	//goQuad->AddComponent(quad);
	//
	//goQuad->zPos = 100;
	//
	//goTileMap2 = new GameObject(&graphics);
	//////The level definition
	//vector<vector<int>> level2;
	//level2 =
	//{
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//	{ 163,163,163,163,163,163,163,163,163,163, },
	//};
	////TileMap
	//tilemap2 = new TileMap(&graphics, &textureManager, L"tileset.png",
	//	32, 32, level2, 16);
	//goTileMap2->AddComponent(tilemap2);
	//goTileMap2->zPos = 100;
	//goTileMap2->xScale = 5;
	//goTileMap2->yScale = 5;
	//camera->AddChildren(goTileMap2);
	//
	//goTileMap = new GameObject(&graphics);
	////The level definition
	//vector<vector<int>> level1;
	//level1 =
	//{
	//	{ 228,229,230,231 },
	//	{ 244,245,246,247 }
	//};
	////TileMap
	//tilemap = new TileMap(&graphics, &textureManager, L"tileset.png",
	//	32, 32, level1, 16);
	//goTileMap->AddComponent(tilemap);
	//goTileMap->zPos=100;
	//goTileMap->xScale = 5;
	//goTileMap->yScale = 5;
	//
	//camera->AddChildren(goTileMap);
	//
	//goSprite = new GameObject(&graphics);
	////Sprite
	//sprite = new Sprite(&graphics, &textureManager);
	//goSprite->AddComponent(sprite);
	//sprite->SetTexture(L"sonic.png");
	//SpriteAnimation * animacion = new SpriteAnimation(6, 6, 129, 57, 35, 35, 0.1);
	//sprite->SetAnimation(animacion);
	//sprite->gameObject->zPos = 100;
	//sprite->gameObject->xPos = -30;
	//camera->AddChildren(goSprite);
	//
	//goSprite2 = new GameObject(&graphics);
	////Sprite2
	//sprite2 = new Sprite(&graphics, &textureManager);
	//goSprite2->AddComponent(sprite2);
	//sprite2->SetTexture(L"characters.png");
	//sprite2->gameObject->xPos= 50;
	//sprite2->gameObject->zPos = 100;
	//sprite2->SetTextureZone(126, 256, 44, 64);
	//camera->AddChildren(goSprite2);
	//
	//sprite->isKinematic = false;
	//sprite2->isKinematic = true;
	//
	//sprite->isTrigger = false;
	//sprite2->isTrigger = false;
	//
	//colManager.AddCollisionable(sprite, 1);
	//colManager.AddCollisionable(sprite2, 2);
	//colManager.AddCollisionable(quad, 2);
	//
	//goQuad2 = new GameObject(&graphics);
	////Quad2
	//quad2 = new Quad(&graphics);
	//goQuad2->AddComponent(quad2);
	//quad2->gameObject->yPos = 50;
	//quad2->gameObject->zPos = 100;
	//goQuad->AddChildren(goQuad2);


	//testCameraBox = new GameObject(&graphics);
	//camera->AddChildren(testCameraBox);
	//
	//
	//minBounds = camera->GetFrustMinBound();
	//maxBounds = camera->GetFrustMaxBound();
	//
	//vector<VertexUV> boundingVertex;
	//boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, minBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, minBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, minBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, minBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(minBounds->x, minBounds->y, maxBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(maxBounds->x, minBounds->y, maxBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(maxBounds->x, maxBounds->y, maxBounds->z, 0.4f, 0.5f));
	//boundingVertex.push_back(VertexUV(minBounds->x, maxBounds->y, maxBounds->z, 0.4f, 0.5f));
	//
	//vector<short> boundingIndeces;
	////Front
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(1);
	//boundingIndeces.push_back(2);
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(2);
	//boundingIndeces.push_back(3);
	////Back
	//boundingIndeces.push_back(4);
	//boundingIndeces.push_back(5);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(4);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(7);
	////Left
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(4);
	//boundingIndeces.push_back(7);
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(7);
	//boundingIndeces.push_back(3);
	////Right
	//boundingIndeces.push_back(1);
	//boundingIndeces.push_back(5);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(1);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(2);
	////Top
	//boundingIndeces.push_back(3);
	//boundingIndeces.push_back(2);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(3);
	//boundingIndeces.push_back(6);
	//boundingIndeces.push_back(7);
	////Down
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(1);
	//boundingIndeces.push_back(5);
	//boundingIndeces.push_back(0);
	//boundingIndeces.push_back(5);
	//boundingIndeces.push_back(4);
	//
	////Multiplicar vertices por matriz de translacion, rotacion y escala
	//
	//testCameraBoxMesh = new Mesh(&graphics, &textureManager, boundingVertex, boundingIndeces);
	//
	//mesh->SetTexture(L"13.jpg");
	//mesh->SetDebugMode(true);
	//testCameraBox->AddComponent(testCameraBoxMesh);







	return true;
}
bool MiJuego::OnUpdate() {
	if (input.GetKey(KeyCode::ESCAPE)) {
		return false;
	}
	//Code to move the quad, it could be putted on a specific script
	//if (input.GetKey(KeyCode::UPARROW)) {
	//	sprite->gameObject->yPos += 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::DOWNARROW)) {
	//	sprite->gameObject->yPos -= 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::RIGHTARROW)) {
	//	sprite->gameObject->xPos += 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::LEFTARROW)) {
	//	sprite->gameObject->xPos -= 50 * Time::deltaTime;
	//}
	//end of quad movement

	if (input.GetKey(KeyCode::SPACE)) {
		goMesh->xPos -= 50 * Time::deltaTime;
	}
	camera->Update();
	return true;
}
void MiJuego::OnDraw() {
	camera->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}