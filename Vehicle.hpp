
#ifndef MTRN3500_VEHICLE_H
#define MTRN3500_VEHICLE_H

#include <iostream>
#include "Shape.hpp"
#include "VectorMaths.hpp"
#include <vector>

class Vehicle : public Shape {
	friend void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_);
public:

	Vehicle();
	virtual ~Vehicle();

	virtual void update(double dt);
	virtual void update(double speed_, double steering_, double dt);

	// abstrac class/ cant use draw function 
	// need own draw function in derived myVehicle class
	virtual void draw() = 0;

	static const int MAX_FORWARD_SPEED_MPS = 10;
	static const int MAX_BACKWARD_SPEED_MPS = -4;
	static const int MAX_LEFT_STEERING_DEGS = 15;
	static const int MAX_RIGHT_STEERING_DEGS = -15;
	static const int VEHICLE_BOUNDS = 3;

	double getSpeed() const { return speed; }
	double getSteering() const { return steering; }

	// function to add more shapes to the vector shape to make own vehicle
	void addShape(Shape * shape);
protected:
	double speed;     // m/s
	double steering;  // degrees

	// vector contain series of shapes to make own vehicle
	std::vector<Shape *> shapes;
};

double clamp(double a, double n, double b);

#endif // for MTRN3500_VEHICLE_H

