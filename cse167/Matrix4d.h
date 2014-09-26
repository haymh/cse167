#ifndef _MATRIX4_H_
#define _MATRIX4_H_
#include "Vector3d.h"
#include "Vector4d.h"

class Matrix4d
{
  protected:
    GLdouble m[4][4];   // matrix elements
    
  public:
    Matrix4d();        // constructor
    Matrix4d(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
	Matrix4d(Vector4d, Vector4d, Vector4d, Vector4d);
    GLdouble* getPointer();  // return pointer to matrix elements
	GLdouble get(int row, int col);
	Matrix4d & multiply(Matrix4d & another);
	Vector4d multiply(Vector4d & another);
    void identity();  // create identity matrix
	void rotateX(GLdouble degree); // rotaion about x axis
	void rotateY(GLdouble degree); // rotation about y axis
	void rotateZ(GLdouble degree); // rotation about z axis
	void rotateArbitrary(Vector3d unit_axis, GLdouble degree); // rotation about an arbitrary axis
	void nonUnifScale(GLdouble sx, GLdouble sy, GLdouble sz);
	void translate(GLdouble x, GLdouble y, GLdouble z);
	void transpose();
	void print();
};

#endif