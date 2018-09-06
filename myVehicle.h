// header file for myVehicle class

#ifndef myVehicle_hpp
#define myVehicle_hpp
#include "Vehicle.hpp"

class myVehicle :public Vehicle {
	// member data
	// member methods
public:
	myVehicle();
	~myVehicle() {}
	void virtual draw();
};

#endif

