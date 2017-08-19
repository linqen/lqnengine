#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	camera = new Camera(&graphics, 60, 0.1f, 1000.0f);

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
	tilemap->SetXPos(-50);
	tilemap->SetYPos(50);
	tilemap->SetZPos(110);

	//The level definition
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
	tilemap2->SetXPos(-50);
	tilemap2->SetYPos(50);
	tilemap2->SetZPos(110);

	//Sprite
	sprite = new Sprite(&graphics, &textureManager);
	sprite->SetTexture(L"sonic.png");
	SpriteAnimation * animacion = new SpriteAnimation(6,6,129,57,35,35,0.1);
	sprite->SetAnimation(animacion);
	sprite->zPos = 100;
	//Sprite2
	sprite2 = new Sprite(&graphics, &textureManager);
	sprite2->SetTexture(L"characters.png");
	sprite2->xPos= 50;
	sprite2->zPos = 100;
	sprite2->SetTextureZone(126, 256, 44, 64);

	//sprite->isKinematic = true;
	//sprite2->isKinematic = true;

	//sprite->isTrigger = true;
	//sprite2->isTrigger = true;

	colManager.AddCollisionable(sprite, 1);
	colManager.AddCollisionable(sprite2, 2);

	//Quad
	quad = new Quad(&graphics);
	quad->yPos = 50;
	quad->xPos = -200;
	quad->zPos = 100;
	movingRight = true;
	return true; 
}
bool MiJuego::OnUpdate() {
	camera->Update();
	sprite->Update();
	sprite2->Update();
	input.GetMouseLocation(mouseX, mouseY);
	//sprite2->xPos = mouseX;
	//sprite2->yPos = -mouseY;
	if (input.GetKey(KeyCode::E)) {
		camera->Yaw(5 * Time::deltaTime);
	}

	if (input.GetKey(KeyCode::Q)) {
		camera->Yaw(-5 * Time::deltaTime);
	}

	if (input.GetKey(KeyCode::W)) {
		camera->MoveForward(5 * Time::deltaTime);
	}

	if (input.GetKey(KeyCode::S)) {
		camera->MoveForward(-5 * Time::deltaTime);
	}
	if (input.GetKey(KeyCode::D)) {
		camera->MoveRight(5 * Time::deltaTime);
	}

	if (input.GetKey(KeyCode::A)) {
		camera->MoveRight(-5 * Time::deltaTime);
	}


	//if (input.GetKey(KeyCode::UPARROW)) {
	//	sprite->yPos += 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::DOWNARROW)) {
	//	sprite->yPos -= 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::RIGHTARROW)) {
	//	sprite->xPos += 50 * Time::deltaTime;
	//}
	//if (input.GetKey(KeyCode::LEFTARROW)) {
	//	sprite->xPos -= 50 * Time::deltaTime;
	//}
	
	if (quad->xPos <= 200&&movingRight) {
		quad->xPos += Time::deltaTime * 50;
		if (quad->xPos >= 200)
			movingRight = false;
	}
	if(!movingRight) {
		quad->xPos -= Time::deltaTime * 50;
		movingRight = false;
			if (quad->xPos <= -200)
				movingRight = true;
	}
	return true;
}
void MiJuego::OnDraw() {
	tilemap2->Draw();
	tilemap->Draw();
	sprite->Draw();
	sprite2->Draw();
	quad->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}