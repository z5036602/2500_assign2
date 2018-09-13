#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "trapPrism.h"

using namespace std;

trapPrism::trapPrism(double base_, double top_, double os1_, double height_, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	base = base_;
	top = top_;
	os1 = os1_;
	height = height_;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x-0.5*base, y, z-0.5*depth);
}

void trapPrism::draw() {
	// draw front face
	setColorInGL();
	positionInGL();
	glBegin(GL_QUADS);
	double os2 = base - top - os1;
	glVertex3f(0, 0, 0);
	glVertex3f(os1, height, 0);
	glVertex3f(base - os2, height, 0);
	glVertex3f(base, 0, 0);

	glEnd();

	// draw the back face
	glBegin(GL_QUADS);

	glVertex3f(0, 0, depth);
	glVertex3f(os1, height, depth);
	glVertex3f(base - os2, height, depth);
	glVertex3f(base, 0, depth);

	glEnd();
	
	// draw the right face
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0,0,depth);
	glVertex3f(os1, height, depth);
	glVertex3f(os1, height, 0);

	glEnd();

	// draw the left face
	glBegin(GL_QUADS);

	glVertex3f(base, 0, 0);
	glVertex3f(base - os2, height, 0);
	glVertex3f(base - os2, height, depth);
	glVertex3f(base, 0, depth);

	glEnd();

	// draw top
	glBegin(GL_QUADS);

	glVertex3f(os1, height, 0);
	glVertex3f(os1, height, depth);
	glVertex3f(base - os2, height, depth);
	glVertex3f(base - os2, height, 0);

	glEnd();

	//draw bottom
	glBegin(GL_QUADS);

	glVertex3f(0,0,0);
	glVertex3f(0, 0, depth);
	glVertex3f(base, 0, depth);
	glVertex3f(base, 0, 0);

	glEnd();
}

