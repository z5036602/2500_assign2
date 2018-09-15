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

#include "Messages.hpp"

#define PI 3.14159265358979323846

myVehicle::myVehicle() {

	Shape *shapePtr = NULL;
	// Body of the car
	shapePtr = new recPrism(10, 2 , 5, 0, 0, 255, 0, 0, 1, 0);
	addShape(shapePtr);
	// Top of the car
	shapePtr = new trapPrism(8, 6, 1, 2, 5, 0, 125, 0, 125, -1, 3, 0);
	addShape(shapePtr);
	// Tail of the car
	shapePtr = new triPrism(3, 1, 45, 8, 180, 255, 0, 0, -4, 5, 0);
	addShape(shapePtr);
	// Bumper
	shapePtr = new triPrism(3, 2, 90, 5, 0, 255, 0, 0, 6.5, 1, 0);
	addShape(shapePtr);
	// Front wheel (sterring and rolling)
	shapePtr = new cylinder(1, 0.5, true, true, 0, 255, 125, 0, 5, 0, -2.75);
	addShape(shapePtr);
	shapePtr = new cylinder(1, 0.5, true, true, 0, 255, 125, 0, 5, 0, 2.75);
	addShape(shapePtr);
	// Rear wheel (rolling)
	shapePtr = new cylinder(1.5, 0.75, true, false, 0, 255, 125, 0, -4, 0, -2.75);
	addShape(shapePtr);
	shapePtr = new cylinder(1.5, 0.75, true, false, 0, 255, 125, 0, -4, 0, 2.75);
	addShape(shapePtr);
}


void myVehicle::update(double speed_, double steering_, double dt) {
	distance += speed * dt;
	Vehicle::update(speed_, steering_, dt);
}

void myVehicle::draw() {
	cylinder *CylObj;
	// all local drawing code
	for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		// move to loval frame of reference
		glPushMatrix();
		positionInGL();
		// inspect if the object being draw is a cylinder using dynamic cast
		if ((CylObj = dynamic_cast<cylinder*>(*it)) != NULL)
		{
			// if the object needed to be steered (front wheel)
			if (CylObj->getIsSteering()) {
				CylObj->setSteeringAngle(steering);
			}
			// if the object needed to be rolled (wheel)
			if (CylObj->getIsRolling()) {
				CylObj->setRollingAngle(distance);
			}
		}
		(*it)->draw();
		glPopMatrix();
	}
}