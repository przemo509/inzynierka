/*
 * Debugger.cpp
 *
 *  Created on: 4 lut 2014
 *      Author: Przemo
 */

#include "Logger.h"
#include "../utils/OpenGLInclude.h"
#include "../Config.h"
#include <cstdio>

using namespace std;

Logger::Logger() {
    guiTextLines.assign(10, "");
}

Logger::~Logger() {
}

void Logger::printOnScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor4fv(config::colorSmokeBright); // taki sam jak dym, żeby konwersja na avi nie dodawała zielonego koloru

    int lineNumber = 1;
    void * font = GLUT_BITMAP_9_BY_15;
    for (vector<string>::iterator v_i = guiTextLines.begin(); v_i != guiTextLines.end(); ++v_i, ++lineNumber) {
        glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - lineNumber * 15);
        string line = *v_i;
        for (string::iterator s_i = line.begin(); s_i != line.end(); ++s_i) {
            char c = *s_i;
            glutBitmapCharacter(font, c);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}
//
//Where font is one of GLUT font constants:
//
//GLUT_BITMAP_8_BY_13
//GLUT_BITMAP_9_BY_15
//GLUT_BITMAP_TIMES_ROMAN_10
//GLUT_BITMAP_TIMES_ROMAN_24
//GLUT_BITMAP_HELVETICA_10
//GLUT_BITMAP_HELVETICA_12
//GLUT_BITMAP_HELVETICA_18

void Logger::addLineToScreen(int lineNumber, char* format, ...) {
    va_list args;	//  Variable argument list
    int len;		//	String length
    char * text;	//	Text

    //  Initialize a variable argument list
    va_start(args, format);

    //  Return the number of characters in the string referenced the list of arguments.
    //  _vscprintf doesn't count terminating '\0' (that's why +1)
    len = _vscprintf(format, args) + 1;

    //  Allocate memory for a string of the specified size
    text = (char *) malloc(len * sizeof(char));

    //  Write formatted output using a pointer to the list of arguments
    vsnprintf(text, len, format, args);

    //  End using variable argument list
    va_end(args);

    guiTextLines[lineNumber] = text;

    //  Free the allocated memory for the string
    free(text);
}
