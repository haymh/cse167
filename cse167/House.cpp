#include "House.h"

House::House(){
	nVerts = 42;
	vertices = new GLfloat[132] {
		-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
		-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
		4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
		4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
		4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
		-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

		-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
		-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
		4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
		-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
		4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

	colors = new GLfloat[132]{
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

		0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
		0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
		0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

	indices = new GLuint[60]{
		0, 2, 3, 0, 1, 2,      // front face
			4, 6, 7, 4, 5, 6,      // left face
			8, 10, 11, 8, 9, 10,     // back face
			12, 14, 15, 12, 13, 14,   // right face
			16, 18, 19, 16, 17, 18,   // top face
			20, 22, 23, 20, 21, 22,   // bottom face

			24, 26, 27, 24, 25, 26,   // grass
			28, 29, 30,             // front attic wall
			31, 33, 34, 31, 32, 33,   // left slope
			35, 37, 38, 35, 36, 37,   // right slope
			39, 40, 41};            // rear attic wall

}