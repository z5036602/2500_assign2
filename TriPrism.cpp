#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "triPrism.h"

using namespace std;

#define PI 3.14159265358979323846

triPrism::triPrism(double a, double b, double angle_, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	alen = a;
	blen = b;
	angle = angle_;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x,  y, z);
}

void triPrism::draw() {
	// setting up position and color in GL
	setColorInGL();
	positionInGL();

	// Front face
	glBegin(GL_TRIANGLES);

	glVertex3f(-alen / 2, 0, -depth / 2); 
	glVertex3f(alen / 2, 0, -depth / 2);
	glVertex3f(-alen / 2 + blen *cos(angle/180 * PI), blen * sin(angle/180 * PI), -depth / 2);
	
	glEnd();

	// Back Face
	glBegin(GL_TRIANGLES);

	glVertex3f(-alen / 2, 0, depth / 2);
	glVertex3f(alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + blen * cos(angle / 180 * PI), blen * sin(angle / 180 * PI), depth / 2);

	glEnd();

	// Right face
	glBegin(GL_QUADS);

	glVertex3f(-alen / 2, 0, -depth / 2);
	glVertex3f(-alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + blen * cos(angle / 180 * PI), blen * sin(angle / 180 * PI), depth / 2);
	glVertex3f(-alen / 2 + blen * cos(angle / 180 * PI), blen * sin(angle / 180 * PI), -depth /2 );

	glEnd();

	// Left face
	glBegin(GL_QUADS);

	glVertex3f(alen / 2, 0, -depth / 2);
	glVertex3f(alen / 2, 0, depth / 2);
	glVertex3f(-alen / 2 + blen * cos(angle / 180 * PI), blen * sin(angle / 180 * PI), depth / 2);
	glVertex3f(-alen / 2 + blen * cos(angle / 180 * PI), blen * sin(angle / 180 * PI), -depth / 2);

	glEnd();
}

