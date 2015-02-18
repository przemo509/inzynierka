/*
 * Camera2.h
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#ifndef CAMERA2_H_
#define CAMERA2_H_

#include <string>
#include "../utils/GeometryUtils.h"

class Keyboard;
class Mouse;

class Camera {
    public:
        Camera();
        virtual ~Camera();

        void toggleFpsMode();
        void rotate(int mouseX, int mouseY);
        void moveUp();
        void moveDown();
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void update(Keyboard* keyboard, Mouse* mouse);

        std::string debugInfo();

        bool isFpsModeOn() const {
            return fpsModeOn;
        }

        float viewAngle;
        float viewMinDistance;
        float viewMaxDistance;

    private:
        bool fpsModeOn;
        float rotationSpeed;
        float horizontalAngle;
        float verticalAngle;
        float movementSpeed;
        Point position;
        Vector direction;

        void moveParallelToView(float amount);
        void movePerpendicularToView(float amount);

        friend class ExplosionVisualization;
};

#endif /* CAMERA2_H_ */
