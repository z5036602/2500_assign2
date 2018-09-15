#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "trapPrism.h"

using namespace std;

trapPrism::trapPrism(double base, double top, double off, double h, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	alen = base;
	blen = top;
	aoff = off;
	height = h;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x, y, z);
}

void trapPrism::draw() {
	// setting up position and color in GL
	setColorInGL();
	positionInGL();

	// Front face
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2, 0, -depth / 2);
	glVertex3f(alen / 2, 0, -depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, -depth / 2);
	glVertex3f(-alen / 2 + aoff, height, -depth / 2);

	glEnd();

	// Back face
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2, 0, depth / 2);
	glVertex3f(alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, depth / 2);
	glVertex3f(-alen / 2 + aoff, height, depth / 2);

	glEnd();

	// Right Face
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2, 0, -depth / 2);
	glVertex3f(-alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + aoff , height, depth / 2);
	glVertex3f(-alen / 2 + aoff , height, -depth / 2);

	glEnd();

	// Left Face
	glBegin(GL_QUADS);

	glVertex3f(alen / 2, 0, -depth / 2);
	glVertex3f(alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, -depth / 2);

	glEnd();

	// Top
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2 + aoff, height, -depth / 2);
	glVertex3f(-alen / 2 + aoff, height, depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, depth / 2);
	glVertex3f(-alen / 2 + aoff + blen, height, -depth / 2);

	glEnd();
	// Bottom
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2, 0, -depth / 2);
	glVertex3f(-alen / 2, 0, depth / 2);
	glVertex3f(alen / 2, 0, depth / 2);
	glVertex3f(alen / 2, 0, -depth / 2);

	glEnd();	
}