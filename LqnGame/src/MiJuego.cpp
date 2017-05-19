#include "..\includes\MiJuego.h"
bool MiJuego::OnInit() {

	cuadradito = new Quad(&graphics);
	return true; 
}
bool MiJuego::OnUpdate() {
	return true;
}
void MiJuego::OnDraw() {
	cuadradito->Draw();
}
bool MiJuego::OnShutDown() {
	return true;
}