#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	//Sprite
	sprite = new Sprite(&graphics, &textureManager);
	sprite->SetTexture(L"sonic.png");
	SpriteAnimation * animacion = new SpriteAnimation(6,6,129,57,35,35,0.15);
	sprite->SetAnimation(animacion);

	//Sprite2
	sprite2 = new Sprite(&graphics, &textureManager);
	sprite2->SetTexture(L"characters.png");
	sprite2->xPos= 500;
	sprite2->SetTextureZone(126, 256, 44, 64);

	//87 175

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