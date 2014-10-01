#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Control.h"
#include "Matrix4d.h"
#include "House.h"
#include "TrunIco.h"
#include "Camera.h"
#include "objreader.h"
#include "Util.h"
#define PI 3.14159265

using namespace std;

static Control control; // control box for translation, scaling, rotation
static Camera cam1(Vector3d(0,0,0), 0, PI);
//soccer ball model
static TrunIco soccer;
//house model
static House house;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
bool Window::toggle = false;
int Window::old_x = 0;
int Window::old_y = 0;
int Window::valid = 0;


enum KEY{ F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12};
KEY key = F1;


// camera setting
GLfloat pitch = 0;
GLfloat yaw = 180;
Vector3d eye(0, 0, 10);

// for loading obj model
GLfloat *vert_array;
GLfloat * norm_array;
GLfloat *tex_array;
int *indi_array;
int vert;
int indi;

static ObjReader objReader;
double obj_color[10] = { 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };

//data for height map
int map_width;
int map_height;
unsigned char* map = NULL;

//matrix for moving camera
Matrix4d translation;

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
  displayCallback();  // call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  
  switch (key){
  case F1:
	  drawCube();
	  break;
  case F2:
	  drawObj();
	  break;
  case F3:
	  drawObj();
	  break;
  case F4:
	  drawObj();
	  break;
  case F5:
	  drawObj();
	  break;
  case F6:
	  drawObj();
	  break;
  case F7:
	  drawSoccer();
	  break;
  case F8:
	  drawHeightMap();
	  break;
  case F9:
	  drawHouse();
	  break;
  }
  
  
  glFlush();  
  glutSwapBuffers();
}

void Window::drawHouse(){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(cam1.getMatrix());
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 60; i++){
		int index = house.indices[i] * 3;
		glColor3f(house.colors[index], house.colors[index + 1], house.colors[index + 2]);
		glVertex3f(house.vertices[index], house.vertices[index + 1], house.vertices[index + 2]);
	}
	glEnd();

}

void Window::drawCube(){
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(control.getMatrix().getPointer());
	control.spinCube();
	// Draw sides of cube in object coordinate system:
	glBegin(GL_QUADS);
	double * color = control.getColor();
	glColor3f(color[0], color[1], color[2]);

	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();
}

void Window::drawSoccer(){
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(control.getMatrix().getPointer());
	control.spinCube();
	//draw soccer ball
	for (int i = 0; i < 12; i++){
		glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.1);
		for (int j = 0; j < 5; j++){
			int index = soccer.pentagon[i][j];
			glVertex3f(soccer.v[index][0], soccer.v[index][1], soccer.v[index][2]);

		}
		glEnd();
	}

	for (int i = 0; i < 20; i++){
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		for (int j = 0; j < 6; j++){
			int index = soccer.hexagon[i][j];
			glVertex3f(soccer.v[index][0], soccer.v[index][1], soccer.v[index][2]);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3f(0.1, 0.1, 0.1);
		for (int j = 0; j < 6; j++){
			int index = soccer.hexagon[i][j];
			glVertex3f(soccer.v[index][0], soccer.v[index][1], soccer.v[index][2]);
		}
		glEnd();
	}
}

void Window::processNormalKeys(unsigned char key, int x, int y){
	switch(key){
		case 99:							//press 'c'
			control.reverse();
			break;
		case 120:
			control.move(LEFT);				//press 'x'
			break;
		case 88:
			control.move(RIGHT);				//press 'X'
			break;
		case 121:
			control.move(DOWN);				//press 'y'
			break;
		case 89:
			control.move(UP);					//press 'Y'
			break;
		case 122:							//press 'z'
			control.move(INWARD);
			break;
		case 90:							//press 'Z'
			control.move(OUTWARD);
			break;
		case 114:							//press 'r'
			control.reset();
			break;
		case 115:							//press 's'
			control.scale(SCALE_DOWN);
			break;
		case 83:							//press 'S'
			control.scale(SCALE_UP);
			break;
		case 97:							//press 'a'
			control.rotateZ(COUNTER_CLOCKWISE);
			break;
		case 65:							//press 'A'
			control.rotateZ(CLOCKWISE);
			break;
		case 98:							//press 'b'
			control.reset();
			toggle = !toggle;
			break;
		case 49:							//press '1'
			control.setColor(RED);
			break;
		case 50:							//press '2'
			control.setColor(GREEN);
			break;
		case 51:							//press '3'
			control.setColor(BLUE);
			break;
		case 52:							//press '4'
			control.setColor(YELLOW);
			break;
		case 27: exit(0);					//press 'ESC'
			break;
	}
}

void Window::processSpecialKeys(int k, int x, int y){
	switch (k){
	case GLUT_KEY_F1:
		key = F1;
		break;
	case GLUT_KEY_F2:
		if (key != F2)
			objReader.readObj("sphere.obj", vert, &vert_array, &norm_array, &tex_array, indi, &indi_array);
		key = F2;
		break;
	case GLUT_KEY_F3:
		if (key != F3)
			objReader.readObj("teddy.obj", vert, &vert_array, &norm_array, &tex_array, indi, &indi_array);
		key = F3;
		break;
	case GLUT_KEY_F4:
		if (key != F4)
			objReader.readObj("teapot.obj", vert, &vert_array, &norm_array, &tex_array, indi, &indi_array);
		key = F4;
		break;
	case GLUT_KEY_F5:
		if (key != F5)
			objReader.readObj("cow.obj", vert, &vert_array, &norm_array, &tex_array, indi, &indi_array);
		key = F5;
		break;
	case GLUT_KEY_F6:
		if (key != F6)
			objReader.readObj("bunny.obj", vert, &vert_array, &norm_array, &tex_array, indi, &indi_array);
		key = F6;
		break;
	case GLUT_KEY_F7:
		key = F7;
		break;
	case GLUT_KEY_F8:
		if (map == NULL){
			map = Util::loadPGM("roi_14.ascii.pgm", map_width, map_height);
			std::cout << map_width << " X " << map_height << std::endl;
		}
			
		key = F8;
		break;
	case GLUT_KEY_F9:
		key = F9;
		break;
	case GLUT_KEY_F10:
		key = F10;
		break;
	case GLUT_KEY_F11:
		key = F11;
		break;
	case GLUT_KEY_F12:
		key = F12;
		break;
	case GLUT_KEY_LEFT:
		yaw += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		yaw -= 0.1;
		break;
	case GLUT_KEY_UP:
		translation.translate(0, 1, 0);
		cam1.translate(translation);
		break;
	case GLUT_KEY_DOWN:
		translation.translate(0, -1, 0);
		cam1.translate(translation);
		break;
	}
}

void Window::mouse_func(int button, int state, int x, int y) {
	old_x = x;
	old_y = y;
	valid = state == GLUT_DOWN;
}

void Window::mouse_wheel(int button, int dir, int x, int y){
	if (dir > 0)
	{
		cam1.zoomIn();
	}
	else
	{
		cam1.zoomOut();
	}

	return;
}

void Window::motion_func(int x, int y) {
	if (valid) {
		int dx = old_x - x;
		int dy = old_y - y;
		/* do something with dx and dy */
		std::cout << "( " << old_x << ", " << old_y << " ), [ " << dx << ", " << dy << " ]" << std::endl;
		cam1.moveHorizontally(dx);
		cam1.moveVertically(-dy);
	}
	old_x = x;
	old_y = y;
}

void Window::drawObj(){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(cam1.getMatrix());
	//glLoadMatrixd(cam1.FPSViewRH(eye, pitch, yaw).getPointer());
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < indi; i++){
		glColor3f(obj_color[i % 10], obj_color[(i + 2) % 10], obj_color[(i + 6) % 10]);
		int index = indi_array[i] * 3;
		glVertex3f(vert_array[index], vert_array[index + 1], vert_array[index + 2]);
	}
	glEnd();
}

void Window::drawHeightMap(){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(cam1.getMatrix());
	glBegin(GL_POINTS);
	double * color = control.getColor();
	glColor3f(color[0], color[1], color[2]);
	int half_width = map_width / 2;
	int half_height = map_height / 2;
	for (int i = 0; i < map_height - 1; i++)
		for (int j = 0; j < map_width - 1; j++){
			glVertex3i(j - half_width, half_height - i, map[i * map_width + j]);
			glVertex3i(j - half_width + 1, half_height - i, map[i * map_width + j + 1]);
			glVertex3i(j - half_width, half_height - i - 1, map[(i + 1) * map_width + j]);
			glVertex3i(j - half_width + 1, half_height - i - 1, map[(i + 1) * map_width + j + 1]);
		}
	glEnd();
}

Control::Control()
{
	reset();
}

Matrix4d& Control::getMatrix()
{
	matrix.identity();
	matrix.multiply(scaling);
	matrix.multiply(rotation);
	matrix.multiply(spin);
	matrix.multiply(translate);
  return matrix;
  
}


void Control::reverse(){
	delta = -delta;
}

void Control::move(DIRECTION d){
	switch (d){
	case LEFT:
		m.translate(-0.5, 0.0, 0.0);
		break;
	case RIGHT:
		m.translate(0.5, 0.0, 0.0);
		break;
	case UP:
		m.translate(0.0, 0.5, 0.0);
		break;
	case DOWN:
		m.translate(0.0, -0.5, 0.0);
		break;
	case INWARD:
		m.translate(0.0, 0.0, -0.5);
		break;
	case OUTWARD:
		m.translate(0.0, 0.0, 0.5);
		break;
	default:
		return;
	}
	translate.multiply(m);
}

void Control::reset(){
	delta = 0.0001;
	spin.identity();
	matrix.identity();
	rotation.identity();
	rotationDirection = COUNTER_CLOCKWISE;
	translate.identity();
	scaling.identity();
	m.identity();
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;
}

void Control::rotateZ(DIRECTION d){
	switch (d){
	case COUNTER_CLOCKWISE:
		m.rotateZ(10);
		break;
	case CLOCKWISE:
		m.rotateZ(-10);
		break;
	default:
		return;
	}
	rotation.multiply(m);
}

void Control::scale(SCALE s){
	switch (s){
	case SCALE_UP:
		m.nonUnifScale(1.1, 1.1, 1.1);
		break;
	case SCALE_DOWN:
		m.nonUnifScale(0.9, 0.9, 0.9);
		break;
	default:
		return;
	}
	scaling.multiply(m);
}

void Control::spinCube(){
	m.rotateY(delta);
	spin.multiply(m);
}

void Control::setColor(COLOR c){
	switch (c){
	case RED:
		color[0] = 1.0;
		color[1] = 0.0;
		color[2] = 0.0;
		break;
	case GREEN:
		color[0] = 0.0;
		color[1] = 1.0;
		color[2] = 0.0;
		break;
	case BLUE:
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 1.0;
		break;
	case YELLOW:
		color[0] = 0.96;
		color[1] = 0.98;
		color[2] = 0.32;
		break;
	}
}

double * Control::getColor(){
	return color;
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);
  glutMotionFunc(Window::motion_func);
  glutMouseFunc(Window::mouse_func);
  glutMouseWheelFunc(Window::mouse_wheel);
    
  // Initialize cube matrix:
  control.reset();
    
  glutMainLoop();
  return 0;
}

