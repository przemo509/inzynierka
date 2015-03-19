/*
 * Vortex.cpp
 *
 *  Created on: 18 lut 2015
 *      Author: Przemo
 */

#include "Vortex.h"
#include "../utils/Timer.h"
#include "../Config.h"
#include <cstdlib> //rand

Vortex::Vortex(int x, int y, int z) {
    startFrame = 20;

    position = Point(x, y, z);
    startingPosition = Point(x, y, z);
    direction = Vector(rand() % 5, rand() % 5, rand() % 5);
    radius = 5;
    lifeFrames = 120;
}

Vortex::~Vortex() {
    // TODO Auto-generated destructor stub
}

bool Vortex::isActive() {
    return Timer::getInstance().getCurrentFrame() > startFrame
            && Timer::getInstance().getCurrentFrame() < startFrame + lifeFrames;
}

void Vortex::apply(vect3f vx, vect3f vy, vect3f vz, int N) {
    if(!isActive()) {
        return;
    }

    for (int k = position.z - radius; k <= position.z + radius; ++k) {
        if(k < 0) continue;
        if(k >= N) break;
        for (int j = position.y - radius; j <= position.y + radius; ++j) {
            if(j < 0) continue;
            if(j >= N) break;
            for (int i = position.x - radius; i <= position.x + radius; ++i) {
                if(i < 0) continue;
                if(i >= N) break;
                Vector windDirection = Vector(position, Point(i, j, k)).crossProduct(direction);
                windDirection.normalize();
                vx[i][j][k] += config::vortexStrenght * windDirection.x;
                vy[i][j][k] += config::vortexStrenght * windDirection.y;
                vz[i][j][k] += config::vortexStrenght * windDirection.z;
            }
        }
    }

    position.x += config::vortexMoving * vx[(int)position.x][(int)position.y][(int)position.z];
    if(position.x < 0 || position.x >= N) position.x = startingPosition.x;

    position.y += config::vortexMoving * vy[(int)position.x][(int)position.y][(int)position.z];
    if(position.y < 0 || position.y >= N) position.y = startingPosition.y;

    position.z += config::vortexMoving * vz[(int)position.x][(int)position.y][(int)position.z];
    if(position.z < 0 || position.z >= N) position.z = startingPosition.z;
}