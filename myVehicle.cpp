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

// Constructor of local vehicle
myVehicle::myVehicle() {
	ShapeInit part;
	// Constructing a vector of shape of own design
	Shape *shapePtr = NULL;
	
	// Body of the car
	shapePtr = new recPrism(10, 2, 5, 0, 0, 255, 0, 0, 1, 0);
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

// Constructor of server vehicle with input of VehicleModel
void myVehicle::convert() {
	// Create a new ShapeInitpart to be push into the vector shapes
	ShapeInit part;
	for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		
		// Write out information about the location, rotation and color of the shape
		part.rgb[0] = (*it)->getRed();
		part.rgb[1] = (*it)->getGreen();
		part.rgb[2] = (*it)->getBlue();
		part.xyz[0] = (*it)->getX();
		part.xyz[1] = (*it)->getY();
		part.xyz[2] = (*it)->getZ();
		part.rotation = (*it)->getRotation();

		// if the shape is Cylinder update parameter of cylinder
		if (dynamic_cast<cylinder*>(*it) != NULL) {
			cylinder *CylObj = dynamic_cast<cylinder*>(*it);
			part.type = CYLINDER;
			part.params.cyl.radius = CylObj->getRadius();
			part.params.cyl.depth = CylObj->getDepth();
			part.params.cyl.isRolling = CylObj->getIsRolling();
			part.params.cyl.isSteering = CylObj->getIsSteering();
		}
		
		// if the shape is recPrism update paramater of rectPrism
		if (dynamic_cast<recPrism*>(*it) != NULL) {
			recPrism *RecObj = dynamic_cast<recPrism*>(*it);
			part.type = RECTANGULAR_PRISM;
			part.params.rect.xlen = RecObj->getXlen();
			part.params.rect.ylen = RecObj->getYlen();
			part.params.rect.zlen = RecObj->getZlen();
		}

		// if the shape is TriPrism update parameters related to triPrism
		if (dynamic_cast<triPrism*>(*it) != NULL) {
			triPrism *TriObj = dynamic_cast<triPrism*>(*it);
			part.type = TRIANGULAR_PRISM;
			part.params.tri.alen = TriObj->getAlen();
			part.params.tri.blen = TriObj->getBlen();
			part.params.tri.angle = TriObj->getAngle();
			part.params.tri.depth = TriObj->getDepth();
		}

		// if the shape is trapPrism update parameter related to trapPrism
		if (dynamic_cast<trapPrism*>(*it) != NULL) {
			trapPrism *TrapObj = dynamic_cast<trapPrism*>(*it);
			part.type = TRAPEZOIDAL_PRISM;
			part.params.trap.alen = TrapObj->getAlen();
			part.params.trap.blen = TrapObj->getBlen();
			part.params.trap.aoff = TrapObj->getAoff();
			part.params.trap.height = TrapObj->getHeight();
			part.params.trap.depth = TrapObj->getDepth();
		}

		// Push the part onto the vector of vehicleModel
		myVehicleModel.shapes.push_back(part);
	}
}

// Converting the designed vehicle to the M message to send to the server
myVehicle::myVehicle(VehicleModel vm) {
	Shape *shapePtr = NULL;
	shapes.clear();
	// going through the vecotr ShapeInit in the vehicle model to convert to proper shapes
	for (std::vector<ShapeInit>::iterator iter = vm.shapes.begin(); iter != vm.shapes.end(); ++iter) {
		// Inspecting the type of shape
		switch (iter->type) {
		case CYLINDER:
			shapePtr = new cylinder(iter->params.cyl.radius, iter->params.cyl.depth, iter->params.cyl.isRolling, iter->params.cyl.isSteering, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;
		case RECTANGULAR_PRISM:
			shapePtr = new recPrism(iter->params.rect.xlen, iter->params.rect.ylen, iter->params.rect.zlen, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;
		case TRIANGULAR_PRISM:
			shapePtr = new triPrism(iter->params.tri.alen, iter->params.tri.blen, iter->params.tri.angle, iter->params.tri.depth, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;
		case TRAPEZOIDAL_PRISM:
			shapePtr = new trapPrism(iter->params.trap.alen, iter->params.trap.blen, iter->params.trap.aoff, iter->params.trap.height, iter->params.trap.depth, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;
		}
		addShape(shapePtr);
	}
}

// Update fucntion to update the information input from the main fucntion
void myVehicle::update(double speed_, double steering_, double dt) {
	distance += speed * dt;
	Vehicle::update(speed_, steering_, dt);
}

// Draw fucntion for local vehicle
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