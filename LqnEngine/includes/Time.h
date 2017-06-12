#ifndef TIME_H
#define TIME_H
#include "Window.h"
#include <timeapi.h>
#pragma comment (lib,"winmm.lib")
class LQN_API Time {
public:
	static double deltaTime;
	static bool Initialize();
	static void SetFrameTime();
private:
	static double pcFreq;
	static double startTime;
	static double lastTime;
};
#endif


