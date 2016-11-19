#include "Keyboard.h"
#include <ctype.h>

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {
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
