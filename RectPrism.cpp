#include <iostream>
#include "RectPrism.h"
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

RectPrism::RectPrism(double length, double height, double depth)
{
	Length = length;
	Depth = depth;
	Height = height;
}

void RectPrism::draw()
{
	//glColor3f(1,1,0);
	//positionInGL();
	glBegin(GL_QUADS);
	//top face

	glVertex3f(Depth / 2.0, Height, Length / 2.0);
	glVertex3f(Depth / 2.0, Height, -Length / 2.0);
	glVertex3f(-Depth / 2.0, Height, -Length / 2.0);
	glVertex3f(-Depth / 2.0, Height, Length / 2.0);

	glEnd();

	//bottom face
	glBegin(GL_QUADS);
	glVertex3f(Depth / 2.0, 0.0, Length / 2.0);
	glVertex3f(Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, Length / 2.0);
	glEnd();
	//back face

	glBegin(GL_QUADS);
	glVertex3f(Depth / 2.0, Height, Length / 2.0);
	glVertex3f(Depth / 2.0, Height, -Length / 2.0);
	glVertex3f(Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(Depth / 2.0, 0.0, Length / 2.0);
	glEnd();
	//front face

	glBegin(GL_QUADS);
	glVertex3f(-Depth / 2.0, Height, Length / 2.0);
	glVertex3f(-Depth / 2.0, Height, -Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, Length / 2.0);
	glEnd();
	//left face

	glBegin(GL_QUADS);
	glVertex3f(Depth / 2.0, Height, Length / 2.0);
	glVertex3f(Depth / 2.0, 0.0, Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, Length / 2.0);
	glVertex3f(-Depth / 2.0, Height, Length / 2.0);
	glEnd();
	//right face

	glBegin(GL_QUADS);
	glVertex3f(Depth / 2.0, Height, -Length / 2.0);
	glVertex3f(Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(-Depth / 2.0, 0.0, -Length / 2.0);
	glVertex3f(-Depth / 2.0, Height, -Length / 2.0);
	glEnd();
}



