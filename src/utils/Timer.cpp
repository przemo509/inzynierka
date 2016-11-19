#include "Timer.h"
#include "../utils/OpenGLInclude.h"
#include "Logger.h"

using namespace std;

Timer::Timer() {
    currentFrame = 0;
    framesInSecond = 0;
    currTime = 0;
    prevTime = 0;
}

Timer::~Timer() {
}

void Timer::incrementFrame() {
    ++currentFrame;
    ++framesInSecond;
    currTime += glutGet(GLUT_ELAPSED_TIME);
    Logger::getInstance().addLineToScreen(0, "Frame: %i", currentFrame);
	int interval = currTime - prevTime;
	if(interval > 1000) {
		prevTime = currTime;
		Logger::getInstance().addLineToScreen(1, "FPS: %f", framesInSecond / (interval / 1000.0f));
		framesInSecond = 0;
	}
}

int Timer::getCurrentTime() {
    return currTime;
}

int Timer::getCurrentFrame() {
    return currentFrame;
}
