// header file for trapPrism shape class

#ifndef trapPrism_hpp
#define trapPrism_hpp
#include "Shape.hpp"

class trapPrism : public Shape {
	// private member data
	// storing length of the base, height, the 2 off set length of right and left
	// depth
	double base;
	double top;
	double os1;
	double height;
	double depth;

	// public memeber methods
public:
	trapPrism() {}
	trapPrism(double base, double top, double os1, double height, double depth, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~trapPrism() {}
	void virtual draw();

};

#endif
