#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4d.h"

enum DIRECTION { LEFT, RIGHT, UP, DOWN, INWARD, OUTWARD, CLOCKWISE, COUNTER_CLOCKWISE };
enum AXIS { X_AXIS, Y_AXIS, Z_AXIS };
enum SCALE { SCALE_UP, SCALE_DOWN };
enum COLOR { RED, GREEN, BLUE, YELLOW };
class Control
{
	
  protected:
    Matrix4d matrix;                 // model matrix
	Matrix4d spin;					// spin matrix
	Matrix4d rotation;				// rotation matrix
	Matrix4d translate;				// translation matrix
	Matrix4d scaling;					// scaling matrix
	Matrix4d m;
	DIRECTION rotationDirection;
	double delta;					// amount of angle change
	double color[3];

  public:
	
    Control();   // Constructor
    Matrix4d& getMatrix();
	void reverse();
	void move(DIRECTION);
	void reset();
	void rotateZ(DIRECTION);
	void scale(SCALE);
	void spinCube();
	void setColor(COLOR);
	double * getColor();
};

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size
	static bool toggle;
	static bool isHouseLoaded;				//indicates if the house is loaded or not
	static int old_x;
	static int old_y;
	static int valid;
	
	static void drawHouse();
	static void drawCube();
	static void drawSoccer();
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int k, int x, int y);
	static void drawObj();
	static void drawHeightMap();
	static void mouse_func(int, int, int, int);
	static void mouse_wheel(int, int, int, int);
	static void motion_func(int, int);
};

#endif

