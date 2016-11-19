#ifndef UTILS_IMAGEUTILS_H_
#define UTILS_IMAGEUTILS_H_

#include "OpenGLInclude.h"
#include <string>

extern "C" {
#include "targa.h"
}

using namespace std;

static void dumpScreenToImage(string fileName) {

    int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int fileDataSize = screenWidth * screenHeight * 3;
    string filePath = "frames/" + fileName;

    GLubyte *pixels = new GLubyte[fileDataSize];
    glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_BYTE, pixels);

    //RLE
    tga_write_rgb_rle(filePath.c_str(), pixels, screenWidth, screenHeight, 24);

    delete pixels;
}

#endif /* UTILS_IMAGEUTILS_H_ */
