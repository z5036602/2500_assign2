// header file for cylinder shape class

#ifndef cylinder_hpp
#define cylinder_hpp
#include "Shape.hpp"

class cylinder : public Shape {
	// private member data
	// storing radius and depth
	double radius;
	double depth;

	// public memeber methods
public:
	cylinder(double radius, double depth, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	cylinder() {}
	void virtual draw();

};

#endif
