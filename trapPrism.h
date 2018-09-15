// header file for trapPrism shape class

#ifndef trapPrism_hpp
#define trapPrism_hpp
#include "Shape.hpp"

class trapPrism : public Shape {
	// private member data
	// storing length of the base, height, the 2 off set length of right and left
	// depth
	double alen;	// length of side A (bottom)
	double blen;	// length of side B (top)
	double aoff;	// off set of side A and B from the left
	double height;	// length along y axis
	double depth;	// length along z axis

	// public memeber methods
public:
	trapPrism() {}
	trapPrism(double base, double top, double off, double h, double d, double rotation_, float red_, float green_, float blue_, double x, double y, double z);
	~trapPrism() {}
	void virtual draw();

};

#endif
