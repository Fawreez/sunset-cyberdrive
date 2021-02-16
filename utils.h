#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>

void Init();
void KeyboardHandler(unsigned char key, int x, int y);
void Reshape(GLsizei width, GLsizei height);
void Display();
void Timer(int value);
GLuint loadTexture(const char* filename);

#endif
