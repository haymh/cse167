#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3d.h"
#include "Matrix4d.h"

class Camera
{
protected:
	Matrix4d * m;   // matrix elements
	// parameters for look at camera
	Vector3d center;
	Vector3d lookat;
	Vector3d up;

	// parameters for FPS camera
	Vector3d eye;
	GLfloat pitch;
	GLfloat yaw;

public:
	Camera(Vector3d, Vector3d, Vector3d);        // Look At Camera constructor
	Camera(Vector3d eye, GLfloat pitch, GLfloat yaw); //FPSView camera constructor
	void setCenter(Vector3d);
	void resetLookat();
	void resetFPS();
	Vector3d getCenter();
	void setLookAt(Vector3d);
	Vector3d getLookAt();
	void setUp(Vector3d);
	Vector3d getUp();
	double * getMatrix();
	void print();
	void moveVertically(int);								// rotate up & down
	void moveHorizontally(int);							// rotate left & right
	void zoomIn();									// zoom in camera
	void zoomOut();									// zoom out camera
	Matrix4d FPSViewRH(Vector3d, GLfloat, GLfloat);

};

#endif