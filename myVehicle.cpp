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


myVehicle::myVehicle(){
	Shape *shapeptr = NULL;
	//shapeptr = new recPrism(10, 4, 8, 0, 0, 0, 255, -0, 5, 0);
	//addShape(shapeptr);
	//shapeptr = new trapPrism(10, 8, 1, 1, 8, 0, 0, 255, 0, 0, 0, 0);
	//addShape(shapeptr);
	shapeptr = new triPrism(50, 20, 45, 5, 0, 125, 0, 200, 0, 0, 0);
	addShape(shapeptr);
	//shapeptr = new cylinder(1,1, 90, 0, 0, 0, true, false,0,0,0);
	//addShape(shapeptr);
	//shapeptr = new cylinder(2, 1, 0, 0, 2, 8.5, true, false,0,0,0);
	//addShape(shapeptr);
	//shapeptr = new cylinder(2, 1, 0, 0, 0, 0, true, true,0,1,0);
	//addShape(shapeptr);
	//shapeptr = new cylinder(2, 1, 0, 10, 2, 8.5, true, true,0,1,0);
	//addShape(shapeptr);

}

myVehicle::myVehicle(VehicleModel Model_) {  //just for testing assign my own value regardless
	Model = Model_;
	/*ShapeInit part;
	Model.remoteID = 0;
	part.type = RECTANGULAR_PRISM;
	part.params.rect.xlen = 10;
	part.params.rect.ylen = 4;
	part.params.rect.zlen = 8;
	part.rgb[0] = 0.0;
	part.rgb[1] = 255;
	part.rgb[2] = 0.0;
	part.rotation = 0.0;
	part.xyz[0] = 0.0;
	part.xyz[1] = 2;
	part.xyz[2] = 0;
	Model.shapes.push_back(part);

	part.type = TRAPEZOIDAL_PRISM;
	part.params.trap.alen = 10;
	part.params.trap.blen = 8;
	part.params.trap.height = 2;
	part.params.trap.aoff = 1;
	part.params.trap.depth = 8;
	part.rgb[0] = 0.7;
	part.rgb[1] = 0.0;
	part.rgb[2] = 0.0;
	part.rotation = 0.0;
	part.xyz[0] = 0;
	part.xyz[1] = 6;
	part.xyz[2] = 0;
	Model.shapes.push_back(part);

	part.type = TRIANGULAR_PRISM;
	part.params.tri.alen = 8;
	part.params.tri.blen = 4.0;
	part.params.tri.angle = 45.0;
	part.params.tri.depth = 8.0;
	part.rgb[0] = 0.0;
	part.rgb[1] = 0.0;
	part.rgb[2] = 0.0;
	part.rotation = 0.0;
	part.xyz[0] = 1.0;
	part.xyz[1] = 8.0;
	part.xyz[2] = 0.0;
	Model.shapes.push_back(part);

	part.type = CYLINDER;
	part.params.cyl.radius = 0.21;
	part.params.cyl.depth = 0.19;
	part.params.cyl.isRolling = 1;
	part.params.cyl.isSteering = 1;
	part.rgb[0] = 0.2;
	part.rgb[1] = 0.2;
	part.rgb[2] = 0.2;
	part.rotation = 0.0;
	part.xyz[0] = 1.28;
	part.xyz[1] = 0.0;
	part.xyz[2] = 0.61;
	Model.shapes.push_back(part);

	part.type = CYLINDER;
	part.params.cyl.radius = 2;
	part.params.cyl.depth = 1;
	part.params.cyl.isRolling = 1;
	part.params.cyl.isSteering = 1;
	part.rgb[0] = 0.2;
	part.rgb[1] = 0.2;
	part.rgb[2] = 0.2;
	part.rotation = 0.0;
	part.xyz[0] = 1.28;
	part.xyz[1] = 0.0;
	part.xyz[2] = -0.61;
	Model.shapes.push_back(part);

	part.type = CYLINDER;
	part.params.cyl.radius = 0.21;
	part.params.cyl.depth = 0.19;
	part.params.cyl.isRolling = 1;
	part.params.cyl.isSteering = 0;
	part.rgb[0] = 0.2;
	part.rgb[1] = 0.2;
	part.rgb[2] = 0.2;
	part.rotation = 0.0;
	part.xyz[0] = -1.04;
	part.xyz[1] = 0.0;
	part.xyz[2] = 0.61;
	Model.shapes.push_back(part);

	part.type = CYLINDER;
	part.params.cyl.radius = 0.21;
	part.params.cyl.depth = 0.19;
	part.params.cyl.isRolling = 1;
	part.params.cyl.isSteering = 0;
	part.rgb[0] = 0.2;
	part.rgb[1] = 0.2;
	part.rgb[2] = 0.2;
	part.rotation = 0.0;
	part.xyz[0] = -1.04;
	part.xyz[1] = 0.0;
	part.xyz[2] = -0.61;
	Model.shapes.push_back(part);*/
	
	Shape *shapeptr =NULL;
	shapes.clear();
	for (std::vector<ShapeInit>::iterator iter = Model.shapes.begin(); iter != Model.shapes.end(); ++iter)//this shapes is a name for vector dont confuse
	{
		switch (iter->type)
		{
		case CYLINDER:
			shapeptr = new cylinder(iter->params.cyl.radius, iter->params.cyl.depth, iter->rotation, iter->xyz[0], iter->xyz[1], iter->xyz[2], iter->params.cyl.isRolling, iter->params.cyl.isSteering,iter->rgb[0], iter->rgb[1], iter->rgb[2]);
			break;

		case RECTANGULAR_PRISM:
			shapeptr = new recPrism(iter->params.rect.xlen, iter->params.rect.ylen, iter->params.rect.zlen, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;

		case TRIANGULAR_PRISM:
			shapeptr = new triPrism(iter->params.tri.alen, iter->params.tri.blen, iter->params.tri.angle, iter->params.tri.depth, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2],iter->xyz[0],iter->xyz[1],iter->xyz[2]);
			break;

		case TRAPEZOIDAL_PRISM:
			shapeptr = new trapPrism(iter->params.trap.alen, iter->params.trap.blen, iter->params.trap.aoff, iter->params.trap.height, iter->rotation, iter->rotation, iter->rgb[0], iter->rgb[1], iter->rgb[2], iter->xyz[0], iter->xyz[1], iter->xyz[2]);
			break;
		}
		addShape(shapeptr);
	}
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

