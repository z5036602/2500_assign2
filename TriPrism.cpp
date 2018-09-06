#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "triPrism.h"

using namespace std;

triPrism::triPrism(double l1_, double l2_, double theta_, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	l1 = l1_;
	l2 = l2_;
	theta = theta_;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setColorInGL();
	setPosition(x, y, z);
	positionInGL();
}

void triPrism::draw() {
	// draw front face
	glBegin(GL_TRIANGLES);

	glVertex3f(l1, 0, 0); 
	glVertex3f(0, 0, 0);
	glVertex3f(l1 - l2 *cosf(theta), l2 * sinf(theta), 0);
	
	glEnd();
	// draw back face
	glBegin(GL_TRIANGLES);

	glVertex3f(l1, 0, depth);
	glVertex3f(0, 0, depth);
	glVertex3f(l1 - l2 * cosf(theta), l2 * sinf(theta), depth);

	glEnd();
	// draw right face
	glBegin(GL_QUADS);

	glVertex3f(0,0,0);
	glVertex3f(0, 0, depth);
	glVertex3f(l1 - l2 * cosf(theta), l2 * sinf(theta), depth);
	glVertex3f(l1 - l2 * cosf(theta), l2 * sinf(theta), 0);

	glEnd();
	// draw left face
	glBegin(GL_QUADS);

	glVertex3f(l1, 0, 0);
	glVertex3f(l1, 0, depth);
	glVertex3f(l1 - l2 * cosf(theta), l2 * sinf(theta), depth);
	glVertex3f(l1 - l2 * cosf(theta), l2 * sinf(theta), 0);

	glEnd();
	// draw bottom
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(l1, 0, depth);
	glVertex3f(l1, 0, 0);

	glEnd();
}

