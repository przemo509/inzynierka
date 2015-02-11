/*
 * Skybox.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#include "Skybox.h"
#include "../utils/OpenGLInclude.h"

Skybox::Skybox() {
	worldSize = 30;
	floorLevel = 0;
	skyLevel = worldSize;
	leftWall = -worldSize/2;
	rightWall = worldSize/2;
	frontWall = worldSize/2;
	backWall = -worldSize/2;
}

Skybox::~Skybox() {
}

void Skybox::draw() {
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    int gridSpacing = 1;
    glColor3f(0.3, 0.3, 0.3);

    glBegin(GL_LINES);
    for(int i = leftWall; i <= rightWall; i += gridSpacing) {
        glVertex3f(i, 0, leftWall);
        glVertex3f(i, 0, rightWall);
        glVertex3f(backWall, 0, i);
        glVertex3f(frontWall, 0, i);
    }
    glEnd();

    glPopMatrix();
}
