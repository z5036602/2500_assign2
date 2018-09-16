// header file for cylinder shape class

#ifndef cylinder_hpp
#define cylinder_hpp
#include "Shape.hpp"

#include "Messages.hpp"

class cylinder : public Shape {
	// private member data
	// storing radius and depth
	double radius;
	double depth;

	// storing if rolling or steering
	// differentiate between front and rear wheel
	bool isRolling;
	bool isSteering;

	// storing value for steering and rolling
	double steering_angle;
	double rolling_angle;

	// public memeber methods
public:
	cylinder(double radius, double depth, bool roll, bool steer, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	cylinder() {}
	void virtual draw();

	double getRadius() { return radius; }
	double getDepth() { return depth; }
	// method for setting the rolling speed/ steering angle
	bool getIsRolling() { return isRolling; }
	bool getIsSteering() { return isSteering; }

	void setRollingAngle(double distance);
	void setSteeringAngle(double angle);

};

#endif
