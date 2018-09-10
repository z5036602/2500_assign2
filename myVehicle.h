// header file for myVehicle class

#ifndef myVehicle_hpp
#define myVehicle_hpp
#include "Vehicle.hpp"
#include "Messages.hpp"

class myVehicle :public Vehicle {
	VehicleModel Model;
	double  distance = 0;
public:
	myVehicle();
	~myVehicle() {}
	void virtual draw();
	void virtual update(double dt);
};

#endif

