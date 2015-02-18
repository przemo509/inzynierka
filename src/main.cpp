/*
 * main.cpp
 *
 * TODO
 *
 *  Created on: 20 sty 2014
 *      Author: Przemo
 */

#include "utils/OpenGLInclude.h"

#include <cstdio>
#include <cstdlib>
#include <string>

#include "devices/Keyboard.h"
#include "devices/Mouse.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "utils/GlutUtils.h"
#include "utils/ImageUtils.h"
#include "utils/Logger.h"
#include "utils/Timer.h"
#include "Config.h"

using namespace std;

Scene scene;
Camera camera;
Keyboard keyboard;
Mouse mouse;
bool blockMouseMove = false;

const int WINDOW_INIT_POS_X = 100;
const int WINDOW_INIT_POS_Y = 100;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const string WINDOW_TITLE = "Symulacja wulkanu";

void initOpenGlEnvironment(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(WINDOW_INIT_POS_X, WINDOW_INIT_POS_Y);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE.c_str());

    glewInit();
    scene.visualization.initFBO(); // musi być po glewInit(), więc nie mogłobyć w konstruktorze Scene()

    glClearColor(0.0, 0.0, 0.0, 1.0); // czyszczenie ekranu na czarno

    glutIgnoreKeyRepeat(1); //TODO co to robi? i jeszcze to: glutSetKeyRepeat()

//		TODO MENU pod prawym przyciskiem myszy
//    msg_submenu = glutCreateMenu(selectMessage);
//    glutAddMenuEntry("abc", 1);
//    glutAddMenuEntry("ABC", 2);
//    color_submenu = glutCreateMenu(selectColor);
//    glutAddMenuEntry("Green", 1);
//    glutAddMenuEntry("Red", 2);
//    glutAddMenuEntry("White", 3);
//    glutCreateMenu(selectFont);
//    glutAddMenuEntry("9 by 15", 0);
//    glutAddMenuEntry("Times Roman 10", 1);
//    glutAddMenuEntry("Times Roman 24", 2);
//    glutAddSubMenu("Messages", msg_submenu);
//    glutAddSubMenu("Color", color_submenu);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//    glutMainLoop();

    //TODO czy co� z tego si� przyda?
    ////	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    ////	GLfloat mat_specular[]   = { 0.7, 0.7,  0.7, 1.0 };
    ////	GLfloat light_position[] = { 0.0, 0.0, 30.0, 1.0 };
    ////	GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };
    ////
    ////	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    ////	glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    ////	glMaterialf( GL_FRONT, GL_SHININESS, 20.0 );
    ////	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    ////	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
    ////
    ////	glShadeModel( GL_SMOOTH );
    ////
    ////	glEnable( GL_LIGHTING );
    ////	glEnable( GL_LIGHT0 );
    ////
    ////	glDepthFunc( GL_LESS );
    ////	glEnable( GL_DEPTH_TEST );
}

void exitProgram() {
    //TODO sprzątanie
    exit(0);
}

void display() {
    Timer::getInstance().incrementFrame();
    if(Timer::getInstance().getCurrentFrame() > config::maxFrames) {
        exitProgram();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

    camera.update(&keyboard, &mouse);

    scene.draw(&camera);
    Logger::getInstance().printOnScreen();

    if (config::dumpFrames) {
        char frameString[20];
        string fileName = string("test_") + itoa(Timer::getInstance().getCurrentFrame(), frameString, 10) + ".tga";
        dumpScreenToImage(fileName);
    }

    glutSwapBuffers();

//    // check OpenGL error
//    	GLenum err;
//    	while ((err = glGetError()) != GL_NO_ERROR) {
//    		printf("OpenGL error: %d\n", err);
//    	}
}

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (height == 0) {
        height = 1;
    }
    GLfloat screenRatio = 1.0 * width / height;

    glViewport(0, 0, width, height);
    gluPerspective(camera.viewAngle, screenRatio, camera.viewMinDistance, camera.viewMaxDistance);

    glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char asciiKey, int mouseX, int mouseY) {
    keyboard.asciiKeyDown(asciiKey);
    if (keyboard.isAsciiKeyPressed(27)) { // ESC
        exitProgram();
    }

    if (keyboard.isAsciiKeyPressed('\t')) {
        camera.toggleFpsMode();
    }
    if (keyboard.isAsciiKeyPressed('r')) {
        scene.simulation.setStartingConditions();
    }
    if (keyboard.isAsciiKeyPressed('q')) {
        scene.simulation.tooglePlayback();
    }

}

void onKeyUp(unsigned char asciiKey, int mouseX, int mouseY) {
    keyboard.asciiKeyUp(asciiKey);
}

void onIdle() {
    scene.simulation.proceed();
    glutPostRedisplay();
}

void onMouseClick(int button, int state, int mouseX, int mouseY) {
    mouse.toggleButton(button, state);
}

void onMouseMove(int mouseX, int mouseY) {
    if (blockMouseMove || !camera.isFpsModeOn()) {
        blockMouseMove = false;
        //zabezpieczenie przed rekurencyjnym wykonaniem w glutWarpPointer poniżej
        return;
    }

    camera.rotate(mouseX, mouseY);

    glutWarpPointer(getWindowMiddleX(), getWindowMiddleY());
    blockMouseMove = true;
}

void addEventListeners() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(onMouseClick);
    glutMotionFunc(onMouseMove);
    glutPassiveMotionFunc(onMouseMove);

    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);

    glutIdleFunc(onIdle);

//    glutTimerFunc(1, onTimerFire, 0); todo
}

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    initOpenGlEnvironment(argc, argv);
    addEventListeners();
    glutMainLoop();
    return 0;

}

