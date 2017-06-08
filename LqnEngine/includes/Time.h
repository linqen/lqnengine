#ifndef TIME_H
#define TIME_H
#include "Window.h"
#include <timeapi.h>
#pragma comment (lib,"winmm.lib")
class LQN_API Time {
public:
	static float deltaTime;
	static bool Initialize();
	static void SetFrameTime();
private:
	static float startTime;
	static float lastTime;
};


#endif


