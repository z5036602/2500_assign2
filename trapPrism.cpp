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
	setPosition(x, y, z);
}

void trapPrism::draw() {
	// draw front face
	setColorInGL();
	positionInGL();
	glBegin(GL_QUADS);
	double os2 = base - top - os1;
	glVertex3f(-0.5*base, 0, -depth*0.5); //a
	glVertex3f(-0.5*base+os1, height, -depth * 0.5);//d
	glVertex3f(0.5*base - os2, height, -depth * 0.5);//c
	glVertex3f(0.5*base, 0, -depth * 0.5);//b

	glEnd();

	// draw the back face
	glBegin(GL_QUADS);

	glVertex3f(-0.5*base, 0, depth * 0.5); //e
	glVertex3f(-0.5*base + os1, height, +depth * 0.5);//h
	glVertex3f(0.5*base - os2, height, +depth * 0.5);//g
	glVertex3f(0.5*base, 0, +depth * 0.5);//f

	glEnd();
	
	// draw the right face
	glBegin(GL_QUADS);

	glVertex3f(0.5*base, 0, -depth * 0.5);
	glVertex3f(0.5*base - os2, height, -depth * 0.5);
	glVertex3f(0.5*base - os2, height, +depth * 0.5);
	glVertex3f(0.5*base, 0, +depth * 0.5);

	glEnd();

	// draw the left face
	glBegin(GL_QUADS);

	glVertex3f(-0.5*base, 0, -depth * 0.5);
	glVertex3f(-0.5*base + os1, height, -depth * 0.5);
	glVertex3f(-0.5*base + os1, height, +depth * 0.5);
	glVertex3f(-0.5*base, 0, depth * 0.5);

	glEnd();

	// draw top
	glBegin(GL_QUADS);

	glVertex3f(-0.5*base + os1, height, -depth * 0.5);
	glVertex3f(0.5*base - os2, height, -depth * 0.5);
	glVertex3f(0.5*base - os2, height, +depth * 0.5);
	glVertex3f(-0.5*base + os1, height, +depth * 0.5);

	glEnd();

	//draw bottom
	glBegin(GL_QUADS);

	glVertex3f(-0.5*base, 0, -depth * 0.5);
	glVertex3f(0.5*base, 0, -depth * 0.5);
	glVertex3f(0.5*base, 0, +depth * 0.5);
	glVertex3f(-0.5*base, 0, depth * 0.5);

	glEnd();
}

