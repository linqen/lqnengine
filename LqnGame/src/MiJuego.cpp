#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

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
}
bool MiJuego::OnShutDown() {
	return true;
}