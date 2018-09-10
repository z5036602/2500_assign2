#ifndef TrapePrism_hpp
#define TrapePrism_hpp

#include "Shape.hpp"

class TrapePrism : public Shape
{
protected:
	double Length;
	double Depth;
	double Height;
public:
	TrapePrism() {}
	TrapePrism(double length, double height, double depth);
	virtual ~TrapePrism() {}
	virtual void TrapePrism();

};
#endif /* RectPrism_hpp */