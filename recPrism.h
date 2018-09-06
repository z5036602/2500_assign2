// header file for recPrism shape class

#ifndef recPrism_hpp
#define recPrism_hpp
#include "Shape.hpp"

class recPrism : public Shape {
	// private member data
	double length;
	double height;
	double depth;

	// public memeber methods
public:
	recPrism() {}
	recPrism(double length, double height, double depth, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~recPrism() {}
	void virtual draw();

};

#endif
