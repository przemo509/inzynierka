/*
 * Timer.cpp
 *
 *  Created on: 4 lut 2014
 *      Author: Przemo
 */

#include "Timer.h"
#include "../utils/OpenGLInclude.h"
#include "Logger.h"

using namespace std;

Timer::Timer() {
    allFrames = 0;
    framesInSecond = 0;
    currTime = 0;
    prevTime = 0;
}

Timer::~Timer() {
}

void Timer::incrementFrame() {
    ++framesInSecond;
    ++allFrames;
    currTime += 1000.0 / 32.0; //= glutGet(GLUT_ELAPSED_TIME);
    Logger::getInstance().addLineToScreen(1, "Frame: %i", framesInSecond);
//	int interval = currTime - prevTime;
//	if(interval > 1000) {
//		prevTime = currTime;
//		Logger::getInstance().addLineToScreen(1, "FPS: %f", framesInSecond / (interval / 1000.0f));
//		framesInSecond = 0;
//	}
}

int Timer::getCurrentTime() {
    return currTime;
}

int Timer::getCurrentFrame() {
    return framesInSecond;
}
