#include <iostream>
#include <Windows.h>
#include <math.h>
#include <tchar.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <vector>

#include "myVehicle.h"
#include "Vehicle.hpp"

#include "cylinder.h"
#include "recPrism.h"
#include "triPrism.h"
#include "trapPrism.h"

myVehicle::myVehicle() {
	Shape *shapePtr = NULL;
	shapePtr = &recPrism(10, 10, 10, -90, 255, 0, 0, 0, 0, 0);
	addShape(shapePtr);
}

void myVehicle::draw() {
	// drawing 1 part a a time
	// body recprism
	// move to the vehicles's local frame of reference
	glPushMatrix();
	positionInGL();

	/* all local drawing code
	for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		prism
	}*/
	recPrism a(8, 4, 10, 0, 0, 0, 255, -4, 2, 0);
	a.draw();

	// move back to the global frame of reference
	glPopMatrix();

	// middle body trapPrism
	glPushMatrix();
	positionInGL();
	trapPrism mb(8, 1, 1, 2, 10, 0, 0, 255, 0, -4, 6, 0);
	mb.draw();
	glPopMatrix();

	// top of the car triPrism
	glPushMatrix();
	positionInGL();
	triPrism top(10,4,45,6,-90,125,0,200,-3,8,10);
	top.draw();
	glPopMatrix();
	 
	// wheels 4 cylinders
	glPushMatrix();
	positionInGL();
	cylinder wrr(3, 0.25, 90, 255, 0, 0, -4, 3, 0);
	wrr.draw();
	glPopMatrix();
	
	glPushMatrix();
	positionInGL();
	cylinder wrl(3, 0.25, -90, 255, 0, 0, 4, 3, 0);
	wrl.draw();
	glPopMatrix();
	
	glPushMatrix();
	positionInGL();
	cylinder wfr(2, 0.25, 90, 255, 0, 0, -4, 2, 10);
	wfr.draw();
	glPopMatrix();
	
	glPushMatrix();
	positionInGL();
	cylinder wfl(2, 0.25, -90, 255, 0, 0, 4, 2, 10);
	wfl.draw();
	glPopMatrix();
	
}