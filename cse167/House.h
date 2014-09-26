#ifndef _HOUSE_H
#define _HOUSE_H

#include "GL\glew.h"

static class House{
public :
	GLfloat* vertices;
	GLfloat* colors;
	GLuint* indices;
	GLuint nVerts = 42;
	House();
};
#endif