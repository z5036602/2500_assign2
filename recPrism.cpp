#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "recPrism.h"

using namespace std;

recPrism::recPrism(double l, double h, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	length = l;
	height = h;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x, y, z);
}

void recPrism::draw() {
	
	positionInGL();
	setColorInGL();
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0, height, 0);
	glVertex3f(length, height, 0);
	glVertex3f(length, 0, 0);
	
	glEnd();
	// draw the back face
	glBegin(GL_QUADS);

	glVertex3f(0, 0, depth);
	glVertex3f(0, height, depth);
	glVertex3f(length, height, depth);
	glVertex3f(length, 0, depth);

	glEnd();

	// draw right face
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(0, height, depth);
	glVertex3f(0, height, 0);

	glEnd();
	
	// draw left side face
	glBegin(GL_QUADS);

	glVertex3f(length, 0, 0);
	glVertex3f(length, 0, depth);
	glVertex3f(length, height, depth);
	glVertex3f(length, height, 0);

	glEnd();
	// draw top
	glBegin(GL_QUADS);

	glVertex3f(0, height, 0);
	glVertex3f(0, height, depth);
	glVertex3f(length, height, depth);
	glVertex3f(length, height,0);
	
	glEnd();

	// draw bottom
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(length, 0, depth);
	glVertex3f(length, 0, 0);

	glEnd();
	
}

