#include "Camera.h"
#include <math.h>

#define ONE_DEGREE 0.0174444


Camera::Camera(Vector3d e, Vector3d d, Vector3d u){
	center = e;
	lookat = d;
	up = u;
	FPSMode = false;
	resetLookat();
}

Camera::Camera(Vector3d e, GLfloat p, GLfloat y){
	eye = e;
	pitch = p;
	yaw = y;
	FPSMode = true;
	resetFPS();
}

void Camera::resetLookat(){
	Vector3d z = center - lookat;
	z.normalize();
	Vector3d x = up.cross(z);
	x.normalize();
	Vector3d y = z.cross(x);
	y.normalize();
	delete m;
	
	m = new Matrix4d(x[0], x[1], x[2], -x.dot(center),
					y[0], y[1], y[2], -y.dot(center),
					z[0], z[1], z[2], -z.dot(center),
					0, 0, 0, 1);
	
}

void Camera::resetFPS(){
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	Vector3d xaxis = { cosYaw, 0, -sinYaw };
	Vector3d yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector3d zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	m = new Matrix4d(
		xaxis[0], xaxis[1], xaxis[2], -xaxis.dot(eye),
		yaxis[0], yaxis[1], yaxis[2], -yaxis.dot(eye),
		zaxis[0], zaxis[1], zaxis[2], -zaxis.dot(eye),
		0, 0, 0, 1
		);
}

void Camera::setCenter(Vector3d e){
	center = e;
	resetLookat();
}
Vector3d Camera::getCenter(){
	return center;
}
void Camera::setLookAt(Vector3d d){
	lookat = d;
	resetLookat();
}
Vector3d Camera::getLookAt(){
	return lookat;
}
void Camera::setUp(Vector3d u){
	up = u;
	resetLookat();
}
Vector3d Camera::getUp(){
	return up;
}
double * Camera::getMatrix(){
	return m -> getPointer();
}
void Camera::print(){

}

void Camera::moveVertically(int amount){
	//pitch -= amount * ONE_DEGREE;
	//resetFPS();
	Matrix4d t;
	t.translate(-eye[0], -eye[1], -eye[2]);
	m->multiply(t);
	t.rotateX(amount * ONE_DEGREE);
	m->multiply(t);
	t.translate(eye[0], eye[1], eye[2]);
	m->multiply(t);
}

void Camera::moveHorizontally(int amount){
	//yaw += amount * ONE_DEGREE;
	//resetFPS();
	Matrix4d t;
	t.translate(-eye[0], -eye[1], -eye[2]);
	m->multiply(t);
	t.rotateY(amount * ONE_DEGREE);
	m->multiply(t);
	t.translate(eye[0], eye[1], eye[2]);
	m->multiply(t);
}

void Camera::zoomIn(){
	Matrix4d s;
	s.nonUnifScale(1.1, 1.1, 1.1);
	m->multiply(s);
}

void Camera::zoomOut(){
	Matrix4d s;
	s.nonUnifScale(0.9, 0.9, 0.9);
	m->multiply(s);
}



// Pitch should be in the range of [-90 ... 90] degrees and yaw
// should be in the range of [0 ... 360] degrees.
Matrix4d Camera::FPSViewRH(Vector3d eye, GLfloat pitch, GLfloat yaw){
	// If the pitch and yaw angles are in degrees,
	// they need to be converted to radians. Here
	// I assume the values are already converted to radians.
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float cosYaw = cos(yaw);
	float sinYaw = sin(yaw);

	Vector3d xaxis = { cosYaw, 0, -sinYaw };
	Vector3d yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector3d zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	Matrix4d viewMatrix(
		xaxis[0], xaxis[1], xaxis[2], -xaxis.dot(eye),
		yaxis[0], yaxis[1], yaxis[2], -yaxis.dot(eye),
		zaxis[0], zaxis[1], zaxis[2], -zaxis.dot(eye),
		0, 0, 0, 1
		);

	return viewMatrix;
}