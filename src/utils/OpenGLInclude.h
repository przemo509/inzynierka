/*
 * Plik nagłówkowy, który należy wykorzystać wszędzie tam,
 * gdzie potrzebny jest dostęp do OpenGL. Włącza on do źródeł
 * pliki nagłówkowe OpenGL we właściwej kolejności. Dzieki
 * temu nie trzeba o niej pamiętać już za każdym razem.
 */

#ifndef OPENGLINCLUDE_H_
#define OPENGLINCLUDE_H_

#define GLEW_STATIC
#include <GL/glew.h> // musi być przed innymi bibliotekami OpenGL

#include <GL/freeglut.h>

#endif /* OPENGLINCLUDE_H_ */
