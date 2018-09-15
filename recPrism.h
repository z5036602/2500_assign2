// header file for recPrism shape class

#ifndef recPrism_hpp
#define recPrism_hpp
#include "Shape.hpp"

class recPrism : public Shape {
	// private member data
	// coordinate of the centre of the base
	double xlen;
	double ylen;
	double zlen;

	// public memeber methods
public:
	recPrism() {}
	recPrism(double xl, double yl, double zl, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~recPrism() {}
	void virtual draw();

};

#endif
