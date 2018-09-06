#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#include "cylinder.h"

using namespace std;

#define PI 3.14159265358979323846

cylinder::cylinder (double radius_, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	radius = radius_;
	depth = d;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setColorInGL();
	setPosition(x, y, z);
	positionInGL();
}

void cylinder::draw() {
	// draw the front face 
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 100; i++)
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100), 0);
	glEnd();
	// draw the back face
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 100; i++)
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100), depth);
	glEnd();
	// draw the cylinder
	gluCylinder(gluNewQuadric(), radius, radius, depth, 30, 10);
}

