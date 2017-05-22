#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	cuadradito = new Quad(&graphics);
	cuadradito->xPos = 500.0f;
	cuadradito->yPos = 500.0f;
	sprite = new Sprite(&graphics);
	sprite->setTexture("C:\\Users\\Sebastianote\\Pictures\\prueba.png");
	return true; 
}
bool MiJuego::OnUpdate() {
	return true;
}
void MiJuego::OnDraw() {
	cuadradito->Draw();
	sprite->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}