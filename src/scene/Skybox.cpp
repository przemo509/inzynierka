/*
 * Skybox.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#include "Skybox.h"

#include <GL/freeglut.h>

Skybox::Skybox() {
	// TODO Auto-generated constructor stub
	worldSize = 100;
	floorLevel = 0;
	skyLevel = worldSize;
	leftWall = -worldSize/2;
	rightWall = worldSize/2;
	frontWall = worldSize/2;
	backWall = -worldSize/2;
}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

void Skybox::draw() {
	glMatrixMode(GL_MODELVIEW);
	// TODO na razie rysujê bia³¹ siatkê na pod³odze, docelowo oteksturowaæ skybox
    glPushMatrix();

    int gridSpacing = 1;
    glColor3f(1, 1, 1);

    for(int i = leftWall; i <= rightWall; i += gridSpacing) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, leftWall);
        glVertex3f(i, 0, rightWall);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(backWall, 0, i);
        glVertex3f(frontWall, 0, i);
        glEnd();
    }

    glPopMatrix();



    //void displaySkyBox()
    //{
    ////	glMatrixMode(GL_MODELVIEW);
    ////	glEnable (GL_TEXTURE_2D);
    ////
    ////	//podloga
    ////	glBindTexture (GL_TEXTURE_2D, woodTexture);
    ////	glPushMatrix();
    ////	glBegin(GL_QUADS);
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, 0.0f);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, FLOOR_REPEAT);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(0.0f, FLOOR_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glEnd();
    ////	glPopMatrix();
    ////
    ////	//sciany
    ////	glBindTexture (GL_TEXTURE_2D, wallTexture);
    ////	glPushMatrix();
    ////	glBegin(GL_QUADS);
    ////	//lewa
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, WALL_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(0.0f, WALL_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	//prawa
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, 0.0f);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, WALL_REPEAT);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	glTexCoord2f(0.0f, WALL_REPEAT);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	//przednia
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, WALL_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	glTexCoord2f(0.0f, WALL_REPEAT);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	//tylna
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, 0.0f);
    ////	glVertex3f(WORLD_BORDER, FLOOR_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(FLOOR_REPEAT, WALL_REPEAT);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(0.0f, WALL_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	glEnd();
    ////	glPopMatrix();
    ////
    ////	//sufit
    ////	glBindTexture (GL_TEXTURE_2D, ceilingTexture);
    ////	glPushMatrix();
    ////	glBegin(GL_QUADS);
    ////	glTexCoord2f(0.0f, 0.0f);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	glTexCoord2f(CEILING_REPEAT, 0.0f);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, WORLD_BORDER);
    ////	glTexCoord2f(CEILING_REPEAT, CEILING_REPEAT);
    ////	glVertex3f(WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	glTexCoord2f(0.0f, CEILING_REPEAT);
    ////	glVertex3f(-WORLD_BORDER, TOP_LVL, -WORLD_BORDER);
    ////	glEnd();
    ////	glPopMatrix();
    ////
    ////	glDisable (GL_TEXTURE_2D);
    //}
}
