#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	camera = new Camera(&graphics, 60, 0.1f, 1000.0f);
	cameraMov = new CameraMovement(&graphics, camera, &input, 300);
	camera->AddComponent(cameraMov);
	camera->SetPosition(D3DXVECTOR3(0.0f, 50.0f, -250.0f));

	goMesh = new GameObject(&graphics);
	camera->AddChildren(goMesh);
	mesh = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	mesh->SetDebugMode(true);
	mesh->SetTexture(L"13.jpg");
	goMesh->AddComponent(mesh);



	goMesh2 = new GameObject(&graphics);
	goMesh->AddChildren(goMesh2);
	mesh2 = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	//mesh2->SetDebugMode(true);
	mesh2->SetTexture(L"13.jpg");
	goMesh2->zPos = -40;
	goMesh2->yPos = 40;
	goMesh2->xPos = -50;
	goMesh2->yRot = 3.14;
	goMesh2->AddComponent(mesh2);



	goMesh3 = new GameObject(&graphics);
	camera->AddChildren(goMesh3);
	mesh3 = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	mesh3->SetDebugMode(true);
	mesh3->SetTexture(L"13.jpg");
	goMesh3->zPos = 40;
	goMesh3->yPos = 40;
	goMesh3->xPos = 150;
	goMesh3->yRot = 3.14;
	goMesh3->AddComponent(mesh3);

	goMesh4 = new GameObject(&graphics);
	camera->AddChildren(goMesh4);
	mesh4 = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	mesh4->SetDebugMode(true);
	mesh4->SetTexture(L"13.jpg");
	goMesh4->zPos = 40;
	goMesh4->yPos = 40;
	goMesh4->xPos = 250;
	goMesh4->yRot = 3.14;
	goMesh4->AddComponent(mesh4);





	//2D game will be out until culling support it
	/*
	goQuad = new GameObject(&graphics);
	camera->AddChildren(goQuad);
	Quad * quad = new Quad(&graphics);
	goQuad->AddComponent(quad);
	
	goQuad->zPos = 100;
	
	goTileMap2 = new GameObject(&graphics);
	////The level definition
	vector<vector<int>> level2;
	level2 =
	{
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
		{ 163,163,163,163,163,163,163,163,163,163, },
	};
	//TileMap
	tilemap2 = new TileMap(&graphics, &textureManager, L"tileset.png",
		32, 32, level2, 16);
	goTileMap2->AddComponent(tilemap2);
	goTileMap2->zPos = 100;
	goTileMap2->xScale = 5;
	goTileMap2->yScale = 5;
	camera->AddChildren(goTileMap2);
	
	goTileMap = new GameObject(&graphics);
	//The level definition
	vector<vector<int>> level1;
	level1 =
	{
		{ 228,229,230,231 },
		{ 244,245,246,247 }
	};
	//TileMap
	tilemap = new TileMap(&graphics, &textureManager, L"tileset.png",
		32, 32, level1, 16);
	goTileMap->AddComponent(tilemap);
	goTileMap->zPos=100;
	goTileMap->xScale = 5;
	goTileMap->yScale = 5;
	
	camera->AddChildren(goTileMap);
	
	goSprite = new GameObject(&graphics);
	//Sprite
	sprite = new Sprite(&graphics, &textureManager);
	goSprite->AddComponent(sprite);
	sprite->SetTexture(L"sonic.png");
	SpriteAnimation * animacion = new SpriteAnimation(6, 6, 129, 57, 35, 35, 0.1);
	sprite->SetAnimation(animacion);
	sprite->gameObject->zPos = 100;
	sprite->gameObject->xPos = -30;
	camera->AddChildren(goSprite);
	
	goSprite2 = new GameObject(&graphics);
	//Sprite2
	sprite2 = new Sprite(&graphics, &textureManager);
	goSprite2->AddComponent(sprite2);
	sprite2->SetTexture(L"characters.png");
	sprite2->gameObject->xPos= 50;
	sprite2->gameObject->zPos = 100;
	sprite2->SetTextureZone(126, 256, 44, 64);
	camera->AddChildren(goSprite2);
	
	sprite->isKinematic = false;
	sprite2->isKinematic = true;
	
	sprite->isTrigger = false;
	sprite2->isTrigger = false;
	
	colManager.AddCollisionable(sprite, 1);
	colManager.AddCollisionable(sprite2, 2);
	colManager.AddCollisionable(quad, 2);
	
	goQuad2 = new GameObject(&graphics);
	//Quad2
	quad2 = new Quad(&graphics);
	goQuad2->AddComponent(quad2);
	quad2->gameObject->yPos = 50;
	quad2->gameObject->zPos = 100;
	goQuad->AddChildren(goQuad2);
	*/




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