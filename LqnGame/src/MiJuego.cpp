#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {
	sprite = new Sprite(&graphics, &textureManager);
	sprite->SetTexture(L"tiles.png");
	sprite->SetAnimation(0, 0, 32, 32, 60);

	sprite2 = new Sprite(&graphics, &textureManager);
	sprite2->SetTexture(L"characters.png");
	sprite2->xPos= -500;
	sprite2->SetTextureZone(126, 256, 44, 64);
	return true; 
}
bool MiJuego::OnUpdate() {
	sprite->Update();
	sprite2->Update();
	return true;
}
void MiJuego::OnDraw() {
	sprite->Draw();
	sprite2->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}