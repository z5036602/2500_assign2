// header file for myVehicle class

#ifndef myVehicle_hpp
#define myVehicle_hpp
#include "Vehicle.hpp"




class myVehicle :public Vehicle {
	double  distance = 0;
public:
	myVehicle();
	~myVehicle() {}
	void virtual draw();
	virtual void update(double speed_, double steering_, double dt);
};

#endif

