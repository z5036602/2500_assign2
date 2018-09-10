#ifndef RectPrism_hpp
#define RectPrism_hpp

#include "Shape.hpp"

class RectPrism : public Shape
{
protected:
	double Length;
	double Depth;
	double Height;
public:
	RectPrism(){}
	RectPrism(double length, double height, double depth);
	virtual ~RectPrism() {}
	virtual void draw();

};
#endif /* RectPrism_hpp */