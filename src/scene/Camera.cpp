/*
 * Camera2.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */


#include "Camera.h"
#include "../utils/OpenGLInclude.h"
#include <cmath>

#include "../devices/Keyboard.h"
#include "../devices/Mouse.h"
#include "../utils/GlutUtils.h"
#include "../utils/Logger.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
	viewAngle = 60.0;
	viewMinDistance = 0.1;
	viewMaxDistance = 100.0;

	rotationSpeed = 0.01;
	horizontalAngle = 1.6;
	verticalAngle = 0.2;
	movementSpeed = 0.5;
	positionX = 0.0;
	positionY = 8.0;
	positionZ = 33.0;

	fpsModeOn = false;
	directionX = cos(horizontalAngle) * cos(verticalAngle);
	directionY = sin(verticalAngle);
	directionZ = sin(horizontalAngle) * cos(verticalAngle);

}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


void Camera::toggleFpsMode() {
	fpsModeOn = !fpsModeOn;

    if(fpsModeOn) {
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(getWindowMiddleX(), getWindowMiddleY());
    }
    else {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

void Camera::rotate(int mouseX, int mouseY) {
	if(fpsModeOn) {
		int dx = mouseX - getWindowMiddleX();
		int dy = mouseY - getWindowMiddleY();

		horizontalAngle += rotationSpeed * dx;
		verticalAngle += rotationSpeed * dy;
		if(verticalAngle > M_PI_2) {
			verticalAngle = M_PI_2;
		} else if(verticalAngle < -M_PI_2) {
			verticalAngle = -M_PI_2;
		}

		directionX = cos(horizontalAngle) * cos(verticalAngle);
		directionY = sin(verticalAngle);
		directionZ = sin(horizontalAngle) * cos(verticalAngle);
    }
}

void Camera::moveUp() {
	positionY += movementSpeed;
}

void Camera::moveDown() {
	positionY -= movementSpeed;
}

void Camera::moveForward() {
	moveParallelToView(-movementSpeed);
}

void Camera::moveBackward() {
	moveParallelToView(movementSpeed);
}

void Camera::moveRight() {
	movePerpendicularToView(movementSpeed);
}

void Camera::moveLeft() {
	movePerpendicularToView(-movementSpeed);
}

void Camera::moveParallelToView(float amount) {
	positionX += amount * directionX;
	positionY += amount * directionY;
	positionZ += amount * directionZ;
}

/**
 * Musimy być na stosie macierzy obiektów
 */
void Camera::update(Keyboard* keyboard, Mouse* mouse) {
	if(fpsModeOn) {
		if(mouse->isLeftButtonPressed()) {
			moveDown();
		}
		if(mouse->isRightButtonPressed()) {
			moveUp();
		}
		if(keyboard->isAsciiKeyPressed('w') || keyboard->isAsciiKeyPressed('W')) {
			moveForward();
		}
		if(keyboard->isAsciiKeyPressed('s') || keyboard->isAsciiKeyPressed('S')) {
			moveBackward();
		}
		if(keyboard->isAsciiKeyPressed('a') || keyboard->isAsciiKeyPressed('A')) {
			moveLeft();
		}
		if(keyboard->isAsciiKeyPressed('d') || keyboard->isAsciiKeyPressed('D')) {
			moveRight();
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //TODO potrzebne? tak samo jak matrix mode?
	gluLookAt(positionX, positionY, positionZ, positionX - directionX, positionY - directionY, positionZ - directionZ, 0.0, 1.0, 0.0);
	Logger::getInstance().addLineToScreen(2, "x %f y %f z %f dirX %f dirY %f dirZ %f", positionX, positionY, positionZ, directionX, directionY, directionZ);
	Logger::getInstance().addLineToScreen(3, "vAng %f hAng %f", verticalAngle, horizontalAngle);
}

void Camera::movePerpendicularToView(float amount) {
	positionX += amount * sin(horizontalAngle);
	positionZ += amount * -cos(horizontalAngle);
}
