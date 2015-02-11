/*
 * ImageUtils.h
 *
 *  Created on: 4 lut 2015
 *      Author: Przemo
 */

#ifndef UTILS_IMAGEUTILS_H_
#define UTILS_IMAGEUTILS_H_

#include "OpenGLInclude.h"
#include <string>

extern "C"
{
	#include "targa.h"
}

using namespace std;

static void dumpScreenToImage(string fileName) {

	int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int fileDataSize = screenWidth * screenHeight * 3;
	string filePath = "frames/" + fileName;

	GLubyte header[18]={0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//	header[12] = screenWidth          & 0xFF;
//	header[13] = ( screenWidth >> 8)  & 0xFF;
//	header[14] = (screenHeight)       & 0xFF;
//	header[15] = (screenHeight >> 8)  & 0xFF;
//	header[16] = 24;
//	// write out the TGA header
//	FILE * file = fopen (filePath.c_str(), "wb");
//
//	fwrite(header,sizeof(GLubyte),18,file);
//	//write out the data:

	GLubyte *pixels = new GLubyte[fileDataSize];
	glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_BYTE, pixels);


	//RLE
	tga_write_rgb_rle(filePath.c_str(), pixels, screenWidth, screenHeight, 24);


//	fwrite(pixels,sizeof(GLubyte),  fileDataSize ,file);
//	fclose(file);
	delete pixels;
}


#endif /* UTILS_IMAGEUTILS_H_ */
