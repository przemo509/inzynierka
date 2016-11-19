#include "Camera.h"
#include "../utils/OpenGLInclude.h"
#include <cmath>

#include "../devices/Keyboard.h"
#include "../devices/Mouse.h"
#include "../utils/GlutUtils.h"
#include "../utils/Logger.h"

Camera::Camera() {
    viewAngle = 60.0;
    viewMinDistance = 0.1;
    viewMaxDistance = 100.0;

    rotationSpeed = 0.01;
    horizontalAngle = 1.6;
    verticalAngle = 0.2;
    movementSpeed = 0.5;
    fpsModeOn = false;

    position = Point(0.0, 8.0, 33.0);
    direction = Vector(cos(horizontalAngle) * cos(verticalAngle), sin(verticalAngle), sin(horizontalAngle) * cos(verticalAngle));

}

Camera::~Camera() {
}

void Camera::toggleFpsMode() {
    fpsModeOn = !fpsModeOn;

    if (fpsModeOn) {
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(getWindowMiddleX(), getWindowMiddleY());
    } else {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

void Camera::rotate(int mouseX, int mouseY) {
    if (fpsModeOn) {
        int dx = mouseX - getWindowMiddleX();
        int dy = mouseY - getWindowMiddleY();

        horizontalAngle += rotationSpeed * dx;
        verticalAngle += rotationSpeed * dy;
        if (verticalAngle > M_PI_2) {
            verticalAngle = M_PI_2;
        } else if (verticalAngle < -M_PI_2) {
            verticalAngle = -M_PI_2;
        }

        direction = Vector(cos(horizontalAngle) * cos(verticalAngle), sin(verticalAngle), sin(horizontalAngle) * cos(verticalAngle));
    }
}

void Camera::moveUp() {
    position.y += movementSpeed;
}

void Camera::moveDown() {
    position.y -= movementSpeed;
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
    position = direction.translate(position, amount);
}

/**
 * Musimy być na stosie macierzy obiektów
 */
void Camera::update(Keyboard* keyboard, Mouse* mouse) {
    if (fpsModeOn) {
        if (mouse->isLeftButtonPressed()) {
            moveDown();
        }
        if (mouse->isRightButtonPressed()) {
            moveUp();
        }
        if (keyboard->isAsciiKeyPressed('w') || keyboard->isAsciiKeyPressed('W')) {
            moveForward();
        }
        if (keyboard->isAsciiKeyPressed('s') || keyboard->isAsciiKeyPressed('S')) {
            moveBackward();
        }
        if (keyboard->isAsciiKeyPressed('a') || keyboard->isAsciiKeyPressed('A')) {
            moveLeft();
        }
        if (keyboard->isAsciiKeyPressed('d') || keyboard->isAsciiKeyPressed('D')) {
            moveRight();
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, position.x - direction.x, position.y - direction.y, position.z - direction.z, 0.0, 1.0, 0.0);
}

void Camera::movePerpendicularToView(float amount) {
    position = Vector(sin(horizontalAngle), 0.0, -cos(horizontalAngle)).translate(position, amount);
}
