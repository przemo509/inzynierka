/*
 * main.cpp
 *
 * TODO
 *
 *  Created on: 20 sty 2014
 *      Author: Przemo
 */


#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstdlib>

#include "devices/Keyboard.h"
#include "devices/Mouse.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "utils/GlutUtils.h"

Scene scene;
Camera camera;
Keyboard keyboard;
Mouse mouse;
bool blockMouseMove = false;

const int WINDOW_INIT_POS_X = 100;
const int WINDOW_INIT_POS_Y = 100;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Symulacja wulkanu";

void initOpenGlEnvironment(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitWindowPosition(WINDOW_INIT_POS_X, WINDOW_INIT_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(WINDOW_TITLE);

    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black TODO czy wystarczy tylko raz?

    glutIgnoreKeyRepeat(1); //TODO co to robi? i jeszcze to: glutSetKeyRepeat()


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

void display() {
//	debug("display");
	glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

    camera.update(&keyboard, &mouse);

    glColor3f(0,1,0);
    glutWireTeapot(0.5);

    scene.draw();

    glutSwapBuffers();
    ////	glFlush(); //oproznia wszystkie bufory nakazujac wykonac sie funkcjom, ktore czekaly na buforowane dane
    //	//zapewnia wykonanie sie funkcji OpenGLa w "skonczonym czasie" (wedlug dokumentacji)
    ////	Sleep(5); //TODO czy potrzebne?, na Linuxie by�oby: sched_yield()
}

void onWindowResize(int width, int height) {
//	debug("resize");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(height == 0) {
		height = 1;
	}
    GLfloat screenRatio = 1.0 * width / height;

    glViewport(0, 0, width, height);
    gluPerspective(camera.viewAngle, screenRatio, camera.viewMinDistance, camera.viewMaxDistance);

    glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char asciiKey, int mouseX, int mouseY) {
//	debug("key down: " + asciiKey);
    if(asciiKey == 27) { // ESC
    	//TODO sprz�tanie
        exit(0);
    }

    if(asciiKey == ' ') {
    	camera.toggleFpsMode();
    }

    keyboard.asciiKeyDown(asciiKey);
}

void onKeyUp(unsigned char asciiKey, int mouseX, int mouseY) {
//	debug("key up: " + asciiKey);
	keyboard.asciiKeyUp(asciiKey);
}

void calculateScene() {
//	debug("calculate scene");
	camera.update(&keyboard, &mouse);
}

void onTimerFire(int passedValue) {
//	debug("timer");
	calculateScene();
    glutTimerFunc(1, onTimerFire, 0);
}

void onIdle() {
	display();
	//void animateExplosion() {
	//	//TODO sprawdzanie czasu, albo tylko liczenie FPS�w, mo�e ju� bez u�ycia timera?
	//	glutPostRedisplay();
	//}
}

void onMouseClick(int button, int state, int mouseX, int mouseY) {
//	debug("mouse click");
	mouse.toggleButton(button, state);
}

void onMouseMove(int mouseX, int mouseY) {
//	debug("mouse move");
	if(blockMouseMove || !camera.isFpsModeOn()) {
//		debug("mouse move blocked");
		blockMouseMove = false;
		//zabezpieczenie przed rekurencyjnym wykonaniem przez glutWarpPointer
		return;
	}

	camera.rotate(mouseX, mouseY);

	glutWarpPointer(getWindowMiddleX(), getWindowMiddleY());
	blockMouseMove = true;
}

void addEventListeners() {
    glutDisplayFunc(display);
    glutReshapeFunc(onWindowResize);

    glutMouseFunc(onMouseClick);
    glutMotionFunc(onMouseMove);
    glutPassiveMotionFunc(onMouseMove);

    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);

    glutIdleFunc(onIdle);

//    glutTimerFunc(1, onTimerFire, 0);
}

int main (int argc, char **argv) {
//	// TODO usun�� je�li nie korzystasz z stdout
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

//	debug("START");

	initOpenGlEnvironment(argc, argv);
	addEventListeners();
	glutMainLoop();
//	debug("END");
    return 0;

}

