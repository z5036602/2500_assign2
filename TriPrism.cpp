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
	//setRotation(rotation_);
	setPosition(x, y, z);
	setRotation(rotation_);
}

void triPrism::draw() {
	// draw front face
	setColorInGL();
	positionInGL();
	//glRotated(50, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glVertex3f(-l1, 0, 0); 
	glVertex3f(0, 0, 0);
	glVertex3f(-l2 *cos(theta/180*3.1415), l2 * sin(theta /180*3.1415), 0);
	
	glEnd();
	// draw back face
	glBegin(GL_TRIANGLES);

	glVertex3f(-l1, 0, depth);
	glVertex3f(0, 0, depth);
	glVertex3f(-l2 * cosf(theta / 180 * 3.1415), l2 * sinf(theta / 180 * 3.1415), depth);

	glEnd();
	// draw right face
	glBegin(GL_QUADS);

	glVertex3f(0,0,0);
	glVertex3f(0, 0, depth);
	glVertex3f(-l2 * cosf(theta / 180 * 3.1415), l2 * sinf(theta / 180 * 3.1415), depth);
	glVertex3f(-l2 * cosf(theta / 180 * 3.1415), l2 * sinf(theta / 180 * 3.1415), 0);

	glEnd();
	// draw left face
	glBegin(GL_QUADS);

	glVertex3f(-l1, 0, 0);
	glVertex3f(-l1, 0, depth);
	glVertex3f(-l2 * cosf(theta / 180 * 3.1415), l2 * sinf(theta / 180 * 3.1415), depth);
	glVertex3f(-l2 * cosf(theta / 180 * 3.1415), l2 * sinf(theta / 180 * 3.1415), 0);

	glEnd();
	// draw bottom
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(-l1, 0, depth);
	glVertex3f(-l1, 0, 0);

	glEnd();
}

