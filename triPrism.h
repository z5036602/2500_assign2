// header file for recPrism shape class

#ifndef triPrism_hpp
#define triPrism_hpp
#include "Shape.hpp"

class triPrism : public Shape {
	// private member data
	// storing length of 2 side of triangle
	// 1 side being a base
	// angle between 2 length theta
	double l1;
	double l2;
	double theta;
	double depth;

	// public memeber methods
public:
	triPrism() {}
	triPrism(double l1, double l2, double theta, double depth, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~triPrism() {}
	void virtual draw();

};

#endif
