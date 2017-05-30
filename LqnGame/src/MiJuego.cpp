#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	cuadradito = new Quad(&graphics);
	cuadradito->xPos = 500.0f;
	cuadradito->yPos = 500.0f;
	sprite = new Sprite(&graphics);
	sprite->SetTexture(L"..\\Textures\\tiles.png");
	//sprite->SetTextureZone(0, 80, 16, 16);
	sprite->SetAnimation(0, 0, 32, 32,60);
	//sprite->setTexture(L"..\\Textures\\prueba.png");
	cuadradito2 = new Quad(&graphics);

	cuadradito2->xPos = -500.0f;
	return true; 
}
bool MiJuego::OnUpdate() {
	sprite->Update();
	return true;
}
void MiJuego::OnDraw() {
	cuadradito->Draw();
	sprite->Draw();
	cuadradito2->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}