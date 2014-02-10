/*
 * GlutUtils.h
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#ifndef GLUTUTILS_H_
#define GLUTUTILS_H_

#include <GL/freeglut_std.h>

static int getWindowMiddleX() {
	return glutGet(GLUT_WINDOW_WIDTH) / 2;
}

static int getWindowMiddleY() {
	return glutGet(GLUT_WINDOW_HEIGHT) / 2;
}


#endif /* GLUTUTILS_H_ */
