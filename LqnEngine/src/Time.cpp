#include "../includes/Time.h"
float Time::lastTime;
float Time::startTime;
float Time::deltaTime;
bool Time::Initialize() {
	startTime = (float)timeGetTime();
	lastTime = startTime;
	SetFrameTime();
	return true;
}
void Time::SetFrameTime() {
	float currTime = (float)timeGetTime();
	//Multiply by 0.001f to make it in milisenconds
	deltaTime = (currTime - lastTime)*0.001f;
	lastTime = currTime;
}