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

cylinder::cylinder (double radius_, double d, double rotation_, double x, double y, double z,bool isRolling_,bool isSteering_,double R_,double G_,double B_) {
	radius = radius_;
	depth = d;
	isRolling = isRolling_;
	isSteering = isSteering_;
	setRotation(rotation_);
	setPosition(x, y+radius_, z-0.5*depth);

	setColor(R_,G_,B_);
}

void cylinder::draw() {
	// draw the front face 
	
	setColorInGL();
	positionInGL();
	if (isSteering == true) {
		glRotatef(-steering_in_cylinder_class, 0, 1, 0);//steering rotate along y
	}
	if (isRolling == true) {
		glRotatef(-distance_in_cylinder_class / radius * 100, 0, 0, 1);//rolling rotate along x
	}
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 100; i++)
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100), 0);
	glEnd();
	glBegin(GL_QUADS);
	for (double theta = 0.0; theta < 180; theta++)
	{
		if (theta == 90)
		{
			glColor3f(0, 0, 1);
		}
		double coor_X = cos(theta)*radius;
		double coor_Y = sin(theta)*radius;
		glVertex3f(coor_X, coor_Y, depth );
		glVertex3f(coor_X, coor_Y, 0);

	}
	glEnd();
	// draw the back face
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 100; i++)
		glVertex3f(radius * cosf(i * 2 * PI / 100), radius * sinf(i * 2 * PI / 100), depth);
	glEnd();
	// draw the cylinder
	gluCylinder(gluNewQuadric(), radius, radius, depth, 30, 10);
	//glRotatef(-rotation, 0, 1, 0);//steering rotate along y
	//glRotatef(-rollTheta, 0, 0, 1);//rolling rotate along x

	
}

void cylinder::setsteering(double steering_) {
	steering_in_cylinder_class = steering_;
}
void cylinder::setrolling_distance(double rolling_distance) {
	distance_in_cylinder_class = rolling_distance;
}
double cylinder::getisRolling(){
	return isRolling;
}
double cylinder::getisSteering(){
	return isSteering;
}