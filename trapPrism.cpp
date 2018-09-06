#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "trapPrism.h"

using namespace std;

trapPrism::trapPrism(double base_, double os1_, double os2_, double height_, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	base = base_;
	os1 = os1_;
	os2 = os2_;
	height = height_;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setColorInGL();
	setPosition(x, y, z);
	positionInGL();
}

void trapPrism::draw() {
	// draw front face
	glBegin(GL_QUADS);

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

