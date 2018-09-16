// header file for myVehicle class

#ifndef myVehicle_hpp
#define myVehicle_hpp
#include "Vehicle.hpp"
#include "Messages.hpp"




class myVehicle :public Vehicle {
	double  distance = 0;
public:
	// Constructor use for design of own vehicle (local)
	myVehicle();
	// Constructor use for design vehicle base on message from the server
	myVehicle(VehicleModel vm);
	// Constructor to convert myVehicle to message using the vector of shape pointer inside
	VehicleModel convert();

	~myVehicle() {}
	void virtual draw();
	virtual void update(double speed_, double steering_, double dt);
};

#endif

