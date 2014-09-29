#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3d.h"
#include "Matrix4d.h"

class Camera
{
protected:
	Matrix4d * m;   // matrix elements
	Vector3d center;
	Vector3d lookat;
	Vector3d up;

public:
	Camera(Vector3d, Vector3d, Vector3d);        // constructor
	void setCenter(Vector3d);
	void reset();
	Vector3d getCenter();
	void setLookAt(Vector3d);
	Vector3d getLookAt();
	void setUp(Vector3d);
	Vector3d getUp();
	double * getMatrix();
	void print();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void forward();
	void backward();
	void leftward();
	void rightward();
	Matrix4d FPSViewRH(Vector3d, GLfloat, GLfloat);

};

#endif