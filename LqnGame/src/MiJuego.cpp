#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	scene = new Scene(&graphics);
	
	goCamera = new GameObject(&graphics);
	scene->AddChildren(goCamera);
	camera = new Camera(&graphics, 60, 0.1f, 1000.0f);
	goCamera->AddComponent(camera);
	cameraMov = new CameraMovement(&graphics, camera, &input, 50);
	goCamera->AddComponent(cameraMov);
	goCamera->zPos = -300;
	camera->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));

	goQuad = new GameObject(&graphics);
	scene->AddChildren(goQuad);
	Quad * quad = new Quad(&graphics);
	goQuad->AddComponent(quad);
	
	goQuad->zPos = 100;

	goMesh = new GameObject(&graphics);
	scene->AddChildren(goMesh);
	mesh = new Mesh(&graphics, &textureManager, "..\\LqnGame\\Meshes\\lobo.obj");
	mesh->SetDebugMode(true);
	goMesh->AddComponent(mesh);
	
	mesh->SetTexture(L"13.jpg");
	mesh->gameObject->zPos = 40;
	mesh->gameObject->yPos = -40;
	mesh->gameObject->xPos = 50;
	mesh->gameObject->yRot = 3.14;


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
	scene->AddChildren(goTileMap2);

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

	scene->AddChildren(goTileMap);

	goSprite = new GameObject(&graphics);
	//Sprite
	sprite = new Sprite(&graphics, &textureManager);
	goSprite->AddComponent(sprite);
	sprite->SetTexture(L"sonic.png");
	SpriteAnimation * animacion = new SpriteAnimation(6, 6, 129, 57, 35, 35, 0.1);
	sprite->SetAnimation(animacion);
	sprite->gameObject->zPos = 100;
	sprite->gameObject->xPos = -30;
	scene->AddChildren(goSprite);

	goSprite2 = new GameObject(&graphics);
	//Sprite2
	sprite2 = new Sprite(&graphics, &textureManager);
	goSprite2->AddComponent(sprite2);
	sprite2->SetTexture(L"characters.png");
	sprite2->gameObject->xPos= 50;
	sprite2->gameObject->zPos = 100;
	sprite2->SetTextureZone(126, 256, 44, 64);
	scene->AddChildren(goSprite2);

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
	return true;
}
bool MiJuego::OnUpdate() {
	if (input.GetKey(KeyCode::ESCAPE)) {
		return false;
	}
	//Code to move the quad, it could be putted on a specific script
	if (input.GetKey(KeyCode::UPARROW)) {
		sprite->gameObject->yPos += 50 * Time::deltaTime;
	}
	if (input.GetKey(KeyCode::DOWNARROW)) {
		sprite->gameObject->yPos -= 50 * Time::deltaTime;
	}
	if (input.GetKey(KeyCode::RIGHTARROW)) {
		sprite->gameObject->xPos += 50 * Time::deltaTime;
	}
	if (input.GetKey(KeyCode::LEFTARROW)) {
		sprite->gameObject->xPos -= 50 * Time::deltaTime;
	}
	//end of quad movement

	scene->Update();
	return true;
}
void MiJuego::OnDraw() {
	scene->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}