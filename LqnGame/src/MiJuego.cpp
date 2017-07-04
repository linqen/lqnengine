#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {
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
	tilemap->SetXPos(-1600);
	tilemap->SetYPos(1600);

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
	tilemap2->SetXPos(-1600);
	tilemap2->SetYPos(1600);

	//Sprite
	sprite = new Sprite(&graphics, &textureManager);
	sprite->SetTexture(L"sonic.png");
	SpriteAnimation * animacion = new SpriteAnimation(6,6,129,57,35,35,0.1);
	sprite->SetAnimation(animacion);
	//Sprite2
	sprite2 = new Sprite(&graphics, &textureManager);
	sprite2->SetTexture(L"characters.png");
	sprite2->xPos= 500;
	sprite2->SetTextureZone(126, 256, 44, 64);

	//sprite->isKinematic = true;
	//sprite2->isKinematic = true;

	//sprite->isTrigger = true;
	//sprite2->isTrigger = true;

	colManager.AddCollisionable(sprite, 1);
	colManager.AddCollisionable(sprite2, 2);

	//Quad
	quad = new Quad(&graphics);
	quad->yPos = 500;
	quad->xPos = -2000;
	movingRight = true;
	return true; 
}
bool MiJuego::OnUpdate() {
	sprite->Update();
	sprite2->Update();
	input.GetMouseLocation(mouseX, mouseY);
	sprite2->xPos = mouseX;
	sprite2->yPos = -mouseY;

	if (input.GetKey(KeyCode::UPARROW)) {
		sprite->yPos += 30;
	}
	if (input.GetKey(KeyCode::DOWNARROW)) {
		sprite->yPos -= 30;
	}
	if (input.GetKey(KeyCode::RIGHTARROW)) {
		sprite->xPos += 30;
	}
	if (input.GetKey(KeyCode::LEFTARROW)) {
		sprite->xPos -= 30;
	}
	
	if (quad->xPos <= 2000&&movingRight) {
		quad->xPos += Time::deltaTime * 500;
		if (quad->xPos >= 2000)
			movingRight = false;
	}
	if(!movingRight) {
		quad->xPos -= Time::deltaTime * 500;
		movingRight = false;
			if (quad->xPos <= -2000)
				movingRight = true;
	}
	return true;
}
void MiJuego::OnDraw() {
	sprite->Draw();
	sprite2->Draw();
	quad->Draw();
	tilemap2->Draw();
	tilemap->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}