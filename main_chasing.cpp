// code to improve upon

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>
#include <math.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"
#include "myVehicle.h"

#include "recPrism.h"
#include "triPrism.h"
#include "trapPrism.h"
#include "cylinder.h"

#include "XBoxController.h"
#include "XInputWrapper.h"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);


#define PI 3.14159265358979323846

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;
double standard_x = 0;
double standard_z = 0;
double standard_speed = 0;
double standard_rotation = 0;
double standard_steering = 0;
double standard_distance = 0;
double my_x = 0;
double my_z = 0;
bool  toggle = false;
double relative_rotation = 0;
double my_rotation = 0;
double relative_rotation_2 = 0;
// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	



	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new myVehicle();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

/*void drawMyShape() {
	cylinder s = cylinder(5,10,true,true,0,255,0,0,0,0,0);
	s.draw();
}*/

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();
	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();
	
	//-----------------------
	// Call the draw function here
	//drawMyShape();
	//-----------------------
	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	
	// XBoxController for Camera
	
	XInputWrapper xinput;
	GamePad::XBoxController controller1(&xinput, 0);

	bool quit = false;
	bool vibrate = false;
	double flag_distance = standard_distance;
	//bool  turn_or_not = false;

	controller1.IsConnected();
	// controll camera by D-pad
	// Left strafe - left dpad
	if (controller1.PressedLeftDpad()) {
		Camera::get()->strafeLeft();
	}
	// Right strafe - right dpad
	if (controller1.PressedRightDpad()) {
		Camera::get()->strafeRight();
	}
	// Foward strafe - up dpad
	if (controller1.PressedUpDpad()) {
		Camera::get()->moveForward();
	}
	// Backward strafe - down dpad
	if (controller1.PressedDownDpad()) {
		Camera::get()->moveBackward();
	}
	// Up strafe using the Right shoulder
	if (controller1.PressedRightShoulder()) {
		Camera::get()->strafeUp();
	}
	// Down strafe using the Left shoulder
	if (controller1.PressedLeftShoulder()) {
		Camera::get()->strafeDown();
	}
	
	// Code for controller Camera using the keyboard
	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	//steering = 0;
	steering = 0;
	// XboxController for Vehicle code
	// Using the right trigger for speed increase
	if (controller1.RightTriggerLocation() != 0) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}
	// Left trigger for reverse
	if (controller1.LeftTriggerLocation() != 0) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}
	// Use left thumb location for steering
	if (controller1.LeftThumbLocation().GetX() < 0) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
	}
	if (controller1.LeftThumbLocation().GetX() > 0) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}
	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS *-1 ;
	}
	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS ;
	}
	// << "my_rotation " << my_rotation << endl;
	//cout << "relative_rotation2 " << relative_rotation_2 << endl;
	double button_pressed = 1;
	if (button_pressed) {
		if (standard_z<10 && standard_z>-10) {
			double my_changed_rotation = ((int)my_rotation + 180) % 360;
			double my_changed_relative = ((int)relative_rotation_2 + 180) % 360;
			cout << "my_changed_rotation " << my_changed_rotation << endl;
			cout << "my_changed_relative " << my_changed_relative << endl;
			if (my_changed_rotation > my_changed_relative + 15) {
				steering = -7;
			}
			else if (my_changed_rotation < my_changed_relative - 15) {
				steering = 7;                                            //negative turns left 
			}
			else {
				steering = 0;
			}
		}
		else {
			if (relative_rotation_2 > my_rotation + 15) {
				steering = 7;
			}
			else if (relative_rotation_2 < my_rotation - 15) {
				steering = -7;                                            //negative turns left 
			}
			else {
				steering = 0;
			}
		}
		if (standard_distance >= 100) {
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
		}
	}
	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}
	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}
	
	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				// converting the local vehicle to message to report online
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					// student code goes here
					// converting myVehicle into message to write to the server
					// converting all shape into parameter suitable for server to write
					myVehicle *myV = dynamic_cast<myVehicle*>(vehicle);
					vm = myV->convert();
					vm.remoteID = 0;

					// reporting the message for local vehicle online
					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		//cout << RemoteDataManager::IsConnected() << endl;
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			my_x = vs.x;
			my_z = vs.z;
			vs.rotation = vehicle->getRotation();
			my_rotation = vs.rotation;
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								// using another constructor to create a new vehicle
								// based on the message received from the server
								// if default constructor just create our own vehicle
								otherVehicles[vm.remoteID] = new myVehicle(vm);

								// more student code goes here
								//
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
									if (vs.remoteID == 1) {
										//cout <<"x_postion"<< vs.x << endl;
										//cout <<"z_postion"<< vs.z << endl;
										//cout << "rotation" << vs.rotation << endl;
										//cout << "steering"<< vs.steering << endl;
										//cout << "speed"<< vs.speed << endl;
										standard_x = vs.x;
										standard_z = vs.z;
										standard_rotation= vs.rotation;
										standard_steering = vs.steering;
										standard_speed = vs.speed;
										standard_distance = (my_x - vs.x)*(my_x - vs.x) + (my_z - vs.z)*(my_z - vs.z);
										if (standard_distance > flag_distance) {
											toggle = true;
										}
										else {
											toggle = false;
										}
										relative_rotation = atan2((vs.z - my_z),(vs.x - my_x)) * 180 / PI;
										relative_rotation_2 = ((int)relative_rotation + 360)%360;
										
									}
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	// update the state of the vehicle speed and steering and position
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react once when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


