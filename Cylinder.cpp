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

cylinder::cylinder (double radius_, double d, bool roll, bool steer, double rotation_, float red_, float green_, float blue_, double x, double y, double z) {
	radius = radius_;
	depth = d;
	isRolling = roll;
	isSteering = steer;
	setColor(red_, green_, blue_);
	setRotation(rotation_);
	setPosition(x , y + radius , z);
}


void cylinder::draw() {
	// setting up position
	positionInGL();
	// rotate the frame of reference depend on rolling and steering
	if (isSteering == true) {
		glRotatef(-steering_angle, 0, 1, 0);	//steering rotate along y
	}
	if (isRolling == true) {
		glRotatef(-rolling_angle, 0, 0, 1);		//rolling rotate along x
	}

	// Front face 
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 50; i++) {
		glColor3f(red, green, blue + 255);
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100) , -depth / 2);
	}
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 50; i <= 100; i++) {
		glColor3f(red, green, blue);
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100) , -depth / 2);
	}
	glEnd();
	// Back face
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 50; i++) {
		glColor3f(red, green, blue + 255);
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100) , depth / 2);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 50; i <= 100; i++) {
		glColor3f(red, green, blue);
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100) , depth / 2);
	}
	glEnd();
	
	setColorInGL();
	// draw the cylinder
	glPushMatrix();
	glTranslated(0, 0, -depth / 2);
	gluCylinder(gluNewQuadric(), radius, radius, depth, 30, 10);
	glPopMatrix();
}

bool cylinder::getIsRolling() {
	return isRolling;
}
bool cylinder::getIsSteering() {
	return isSteering;
}

void cylinder::setRollingAngle(double distance) {
	rolling_angle = distance/radius*100;
}
void cylinder::setSteeringAngle(double angle) {
	steering_angle = angle;
}

double cylinder::getRadius() {
	return radius;
}
double cylinder::getDepth() {
	return depth;
}

