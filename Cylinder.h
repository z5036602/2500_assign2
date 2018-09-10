// header file for cylinder shape class

#ifndef cylinder_hpp
#define cylinder_hpp
#include "Shape.hpp"

class cylinder : public Shape {
	double radius;
	double depth;
	bool isRolling = true;	// needs to roll with vehicle?
	bool isSteering = true;// needs to steer with vehicle?
	double steering_in_cylinder_class;
	double distance_in_cylinder_class;
public:
	cylinder(double radius, double depth, double rotation_, double x, double y, double z,bool isRolling_, bool isSteering_);
	cylinder() {}
	void virtual draw();
	void setsteering(double steering_);
	void setrolling_distance(double rolling_distance);
	//double ThetaRolling(double speed, double time);
	double getisRolling();
	double getisSteering();
};

#endif
