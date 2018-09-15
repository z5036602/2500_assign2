// header file for recPrism shape class

#ifndef triPrism_hpp
#define triPrism_hpp
#include "Shape.hpp"

class triPrism : public Shape {
	// private member data
	double alen;	// length of side A (bottom)
	double blen;	// length of side B (left)
	double angle;	// angle (between side A and B)
	double depth;	// length along z axis
	// public memeber methods
public:
	triPrism() {}
	triPrism(double a, double b, double angle, double depth, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~triPrism() {}
	void virtual draw();

};

#endif
