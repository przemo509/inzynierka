/*
 * Keyboard.cpp
 *
 *  Created on: 23 sty 2014
 *      Author: Przemo
 */

#include "Keyboard.h"
#include <ctype.h>

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
    asciiKeys[tolower(key)] = true;
    asciiKeys[toupper(key)] = true;
}

void Keyboard::asciiKeyUp(unsigned char key) {
    asciiKeys[tolower(key)] = false;
    asciiKeys[toupper(key)] = false;
}
