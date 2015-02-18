/*
 * GlutUtils.h
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#ifndef GLUTUTILS_H_
#define GLUTUTILS_H_

#include "../utils/OpenGLInclude.h"
#include "GeometryUtils.h"

static int getWindowMiddleX() {
    return glutGet(GLUT_WINDOW_WIDTH) / 2;
}

static int getWindowMiddleY() {
    return glutGet(GLUT_WINDOW_HEIGHT) / 2;
}

static void drawPoint(const Point &p) {
    glVertex3f(p.x, p.y, p.z);
}

static void drawLine(const Point &a, const Point &b) {
    drawPoint(a);
    drawPoint(b);
}

static void drawVector(const Point &p, const Vector &v) {
    drawPoint(p);
    drawPoint(v.translate(p));
}

#endif /* GLUTUTILS_H_ */
