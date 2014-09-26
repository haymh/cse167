#include "Camera.h"

Camera::Camera(Vector3d e, Vector3d d, Vector3d u){
	center = e;
	lookat = d;
	up = u;
	reset();
}

void Camera::reset(){
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
void Camera::setCenter(Vector3d e){
	center = e;
	reset();
}
Vector3d Camera::getCenter(){
	return center;
}
void Camera::setLookAt(Vector3d d){
	lookat = d;
	reset();
}
Vector3d Camera::getLookAt(){
	return lookat;
}
void Camera::setUp(Vector3d u){
	up = u;
	reset();
}
Vector3d Camera::getUp(){
	return up;
}
double * Camera::getMatrix(){
	return m -> getPointer();
}
void Camera::print(){

}