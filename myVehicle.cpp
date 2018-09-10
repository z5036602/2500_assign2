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
	
	Shape *shapeptr;

	//shapes.clear();
	shapeptr = new recPrism(10, 4, 8, 0, 0, 0, 255, -0, 2, 0);
	addShape(shapeptr);
	shapeptr = new trapPrism(10, 1, 1, 2, 8, 0, 0, 255, 0, 0, 6, 0);
	addShape(shapeptr);
	shapeptr = new triPrism(8, 4, 45, 8, 0, 125, 0, 200, 1, 8, 0);
	addShape(shapeptr);
	shapeptr = new cylinder(2, 1, 0, 0, 2, -1,true,false);
	addShape(shapeptr);
	shapeptr = new cylinder(2, 1, 0, 0, 2, 8.5,true,false);
	addShape(shapeptr);
	shapeptr = new cylinder(2, 1, 0, 10, 2, -1,true,true);
	addShape(shapeptr);
	shapeptr = new cylinder(2, 1, 0, 10, 2, 8.5,true,true);
	addShape(shapeptr);
}

void myVehicle::update( double dt) {
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;

	distance += speed * dt;


}

void myVehicle::draw() {
	cylinder *CylObj;
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++)
	{
		//move to the vehicle's local frame of reference
		glPushMatrix();
		positionInGL();
		//draw in local frame
		if ((CylObj = dynamic_cast<cylinder*>(*it)) != NULL)
		{
			if (CylObj->getisSteering()) {
				CylObj->setsteering(steering);
			}
			if (CylObj->getisRolling()) {
				CylObj->setrolling_distance(distance);
			}
		}
		(*it)->draw();
		//move back to global frame of reference
		glPopMatrix();

	}



}

