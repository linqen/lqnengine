#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
using namespace std;
#include "ImportExport.h"

class LQN_API SpriteAnimation {
public:
	int mtotalFrames, mframesbyWidth;
	float moffSetX, moffSetY, mframeWidth, mframeHeight, manimTime;
	//Configure animation, time based on seconds
	SpriteAnimation(int totalFrames, int framesbyWidth, float offSetX, float offSetY, float frameWidth, float frameHeight,float animTime) {
		mtotalFrames = totalFrames;
		mframesbyWidth = framesbyWidth;
		moffSetX = offSetX;
		moffSetY = offSetY;
		mframeWidth = frameWidth;
		mframeHeight = frameHeight;
		manimTime = animTime;
	}
};


#endif