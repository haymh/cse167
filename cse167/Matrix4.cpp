#include <math.h>
#include <iostream>

#include "Matrix4d.h"
#define PI 3.14159265

Matrix4d::Matrix4d()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 
Matrix4d::Matrix4d(
  GLdouble m00, GLdouble m01, GLdouble m02, GLdouble m03,
  GLdouble m10, GLdouble m11, GLdouble m12, GLdouble m13,
  GLdouble m20, GLdouble m21, GLdouble m22, GLdouble m23,
  GLdouble m30, GLdouble m31, GLdouble m32, GLdouble m33 )
{
  m[0][0] = m00;
  m[1][0] = m01;
  m[2][0] = m02;
  m[3][0] = m03;
  m[0][1] = m10;
  m[1][1] = m11;
  m[2][1] = m12;
  m[3][1] = m13;
  m[0][2] = m20;
  m[1][2] = m21;
  m[2][2] = m22;
  m[3][2] = m23;
  m[0][3] = m30;
  m[1][3] = m31;
  m[2][3] = m32;
  m[3][3] = m33;
}

Matrix4d::Matrix4d(Vector4d col1, Vector4d col2, Vector4d col3, Vector4d col4){
	for (int i = 0; i < 4; i++){
		m[i][0] = col1[i];
		m[i][1] = col2[i];
		m[i][2] = col3[i];
		m[i][3] = col4[i];
	}
}


GLdouble* Matrix4d::getPointer()
{
  return &m[0][0];
}

void Matrix4d::identity()
{
  GLdouble ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

void Matrix4d::rotateX(GLdouble angle){
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = -sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4d::rotateY(GLdouble angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = -sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4d::rotateZ(GLdouble angle){
	m[0][0] = cos(angle);
	m[0][1] = sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = -sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4d::rotateArbitrary(Vector3d a, GLdouble angle){
	a.normalize();
	GLdouble s = sin(angle);
	GLdouble c = cos(angle);
	GLdouble xx = a[0] * a[0];
	GLdouble yy = a[1] * a[1];
	GLdouble zz = a[2] * a[2];
	GLdouble xy = a[0] * a[1];
	GLdouble xz = a[0] * a[2];
	GLdouble yz = a[1] * a[2];
	m[0][0] = xx + c * (1 - xx);
	m[0][1] = xy * (1 - c) - a[2] * s;
	m[0][2] = xz * (1 - c) + a[1] * s;
	m[0][3] = 0;
	m[1][0] = xy * (1 - c) + a[2] * s;
	m[1][1] = yy + c * (1 - yy);
	m[1][2] = yz * (1 - c) - a[0] * s;
	m[1][3] = 0;
	m[2][0] = xz * (1 - c) - a[1] * s;
	m[2][1] = yz * (1 - c) + a[0] * s;
	m[2][2] = zz + c * (1 - zz);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

GLdouble Matrix4d::get(int row, int col){
	return m[row][col];
}

void Matrix4d::nonUnifScale(GLdouble sx, GLdouble sy, GLdouble sz){
	m[0][0] = sx;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = sy;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = sz;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4d::translate(GLdouble x, GLdouble y, GLdouble z){
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	m[3][3] = 1;
}

void Matrix4d::transpose(){
	for (int i = 0; i < 3; i++)
		for (int j = i + 1; j < 4; j++){
			GLdouble temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
}

void Matrix4d::print(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix4d & Matrix4d::multiply(Matrix4d & another){
	GLdouble row[4];
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			row[j] = 0.0;
			for (int k = 0; k < 4; k++)
				row[j] += m[i][k] * another.get(k, j);
		}
		for (int j = 0; j < 4; j++)
			m[i][j] = row[j];
	}
	return *this;
}

Vector4d Matrix4d::multiply(Vector4d & another){
	Vector4d v;
	GLdouble x = 0.0;
	for (int i = 0; i < 4; i++){
		x = 0.0;
		for (int j = 0; j < 4; j++){
			x += m[i][j] * another[j];
		}
		v.set(i, x);
	}
	return v;
}

Vector3d Matrix4d::multiply(Vector3d & another){
	Vector4d v(another[0], another[1], another[2], 1);
	v = multiply(v);
	Vector3d r(v[0], v[1], v[2]);
	return r;
}

