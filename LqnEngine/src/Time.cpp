#include "../includes/Time.h"
double Time::pcFreq=0;
double Time::lastTime=0;
double Time::startTime=0;
double Time::deltaTime=0;
DWORD_PTR old_mask;

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

void Time::SetFrameTime() {
	old_mask = SetThreadAffinityMask(GetCurrentThread, 1);
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double currTime = double(li.QuadPart);
	deltaTime = double(currTime - lastTime) / pcFreq;
	lastTime = currTime;
	SetThreadAffinityMask(GetCurrentThread, old_mask);
}