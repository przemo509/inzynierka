/*
 * Keyboard.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#include "Keyboard.h"

Keyboard::Keyboard() {
	// TODO Auto-generated constructor stub

}

Keyboard::~Keyboard() {
	// TODO Auto-generated destructor stub
}

bool Keyboard::isAsciiKeyPressed(unsigned char key) {
	return asciiKeys[key];
}

void Keyboard::asciiKeyDown(unsigned char key) {
	asciiKeys[key] = true;
}

void Keyboard::asciiKeyUp(unsigned char key) {
	asciiKeys[key] = false;
}
