#include "Logger.h"
#include "../utils/OpenGLInclude.h"
#include "Config.h"
#include <cstdio>

using namespace std;

Logger::Logger() {
    guiTextLines.assign(25, "");
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

    glColor4fv(Config::getInstance()->colorSmokeBright); // taki sam jak dym, żeby konwersja na avi nie dodawała zielonego koloru

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

void Logger::addLineToScreen(int lineNumber, const char* format, ...) {
    va_list args;
    int len;
    char * text;

    va_start(args, format);
    len = _vscprintf(format, args) + 1;
    text = (char *) malloc(len * sizeof(char));
    vsnprintf(text, len, format, args);

    va_end(args);

    guiTextLines[lineNumber] = text;

    free(text);
}
