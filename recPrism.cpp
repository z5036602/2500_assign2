#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "recPrism.h"

using namespace std;

recPrism::recPrism(double xl, double yl, double zl, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	xlen = xl;
	ylen = yl;
	zlen = zl;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x, y, z);
}

void recPrism::draw() {
	// setting up position and color in GL
	setColorInGL();
	positionInGL();

	// Front face
	glBegin(GL_QUADS);

	glVertex3f(-xlen/2 , 0, -zlen/2);
	glVertex3f(xlen/2, 0, -zlen / 2);
	glVertex3f(xlen/2, ylen, -zlen / 2);
	glVertex3f(-xlen/2, ylen, -zlen / 2);

	glEnd();

	// Back face
	glBegin(GL_QUADS);

	glVertex3f(-xlen / 2, 0, zlen / 2);
	glVertex3f(xlen / 2, 0, zlen / 2);
	glVertex3f(xlen / 2, ylen, zlen / 2);
	glVertex3f(-xlen / 2, ylen, zlen / 2);

	glEnd();

	// Right face
	glBegin(GL_QUADS);

	glVertex3f(-xlen / 2, 0, -zlen / 2);
	glVertex3f(-xlen / 2, 0, zlen / 2);
	glVertex3f(-xlen / 2, ylen, zlen / 2);
	glVertex3f(-xlen / 2, ylen, -zlen / 2);

	glEnd();

	// Left face
	glBegin(GL_QUADS);

	glVertex3f(xlen / 2, 0, -zlen / 2);
	glVertex3f(xlen / 2, 0, zlen / 2);
	glVertex3f(xlen / 2, ylen, zlen / 2);
	glVertex3f(xlen / 2, ylen, -zlen / 2);

	glEnd();

	// Top
	glBegin(GL_QUADS);

	glVertex3f(xlen / 2, ylen, -zlen / 2);
	glVertex3f(xlen / 2, ylen, zlen / 2);
	glVertex3f(-xlen / 2, ylen, zlen / 2);
	glVertex3f(-xlen / 2, ylen, -zlen / 2);

	glEnd();

	// Bottom
	glBegin(GL_QUADS);

	glVertex3f(xlen / 2, 0, -zlen / 2);
	glVertex3f(xlen / 2, 0, zlen / 2);
	glVertex3f(-xlen / 2, 0, zlen / 2);
	glVertex3f(-xlen / 2, 0, -zlen / 2);

	glEnd();
}

