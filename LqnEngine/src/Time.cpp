#include "../includes/Time.h"
double Time::pcFreq=0;
double Time::lastTime=0;
double Time::startTime=0;
double Time::deltaTime=0;
//bool Time::Initialize() {
//	startTime = (float)timeGetTime();
//	lastTime = startTime;
//	SetFrameTime();
//	return true;
//}
bool Time::Initialize() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		return false;

	pcFreq = double(li.QuadPart);

	QueryPerformanceCounter(&li);
	startTime = li.QuadPart;
	lastTime = startTime;
	return true;
}
//void Time::SetFrameTime() {
//	float currTime = (float)timeGetTime();
//	//Multiply by 0.001f to make it in milisenconds
//	deltaTime = (currTime - lastTime)*0.001f;
//	lastTime = currTime;
//}
void Time::SetFrameTime() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double currTime = double(li.QuadPart);
	deltaTime = double(currTime - lastTime) / pcFreq;
	lastTime = currTime;
}