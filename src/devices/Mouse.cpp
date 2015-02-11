/*
 * Mouse.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#include "Mouse.h"
#include "../utils/OpenGLInclude.h"

Mouse::Mouse() {
	// TODO Auto-generated constructor stub
	leftButtonPressed = false;
	rightButtonPressed = false;
}

Mouse::~Mouse() {
	// TODO Auto-generated destructor stub
}

void Mouse::toggleButton(int button, int state) {
	if(button == GLUT_LEFT_BUTTON) {
		leftButtonPressed = state == GLUT_DOWN;
	}
	else if(button == GLUT_RIGHT_BUTTON) {
		rightButtonPressed = state == GLUT_DOWN;
	}
}

bool Mouse::isLeftButtonPressed() const {
	return leftButtonPressed;
}

bool Mouse::isRightButtonPressed() const {
	return rightButtonPressed;
}
