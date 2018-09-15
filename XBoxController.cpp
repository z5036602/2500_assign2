// Ngoc Diep Do (z3411678)
// XBoxController.h implementation file
// Last edited (19/8/2018)


#include <iostream>
#include <Windows.h>
#include <xinput.h>
#include <math.h>
#include "XBoxController.h"
#include "XInputWrapper.h"


// Class XBoxController's method
// Constructor
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {
	// copy the input argument to the class member variable xinput
	this->xinput = xinput;
	// copy the input argument to the class member data
	_controllerId = id;
}

// Method which report information relating to the specific controller
DWORD GamePad::XBoxController::GetControllerId() {
	return _controllerId;
}

// Methods which report particular aspects of controller status
// Determine if the controller is connected
bool GamePad::XBoxController::IsConnected() {

	this->xinput = xinput;
	xinput->XInputGetState(_controllerId, &_controllerState);

	bool result = false;

	// setting the memory space to zero
	memset(&_controllerState, 0, sizeof(XINPUT_STATE));

	// Getting and inspecting the state
	DWORD state = XInputGetState(_controllerId, &_controllerState);
	if (state == ERROR_SUCCESS) {
		result = true;
	}
	return result;
}

// Determine if A is pressed
bool GamePad::XBoxController::PressedA() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState 
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		result = true;
	}
	return result;
}

// Determine if B is pressed
bool GamePad::XBoxController::PressedB() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		result = true;
	}
	return result;
}

// Determine if X is pressed
bool GamePad::XBoxController::PressedX() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		result = true;
	}
	return result;
}

// Determine if Y is pressed
bool GamePad::XBoxController::PressedY() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		result = true;
	}
	return result;
}

// Determine if LeftTrigger is pressed
bool GamePad::XBoxController::PressedLeftShoulder() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		result = true;
	}
	return result;
}

// Determine if RightTrigger is pressed
bool GamePad::XBoxController::PressedRightShoulder() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		result = true;
	}
	return result;
}

// Determine if Down on D-pad is pressed
bool GamePad::XBoxController::PressedDownDpad() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		result = true;
	}
	return result;
}

// Determine if Up on D-pad is pressed
bool GamePad::XBoxController::PressedUpDpad() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		result = true;
	}
	return result;
}

// Determine if Left on D-pad is pressed
bool GamePad::XBoxController::PressedLeftDpad() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		result = true;
	}
	return result;
}

// Determine if Right on D-pad is pressed
bool GamePad::XBoxController::PressedRightDpad() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		result = true;
	}
	return result;
}

// Determine if Start button is pressed
bool GamePad::XBoxController::PressedStart() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		result = true;
	}
	return result;
}

// Determine if Back button is pressed
bool GamePad::XBoxController::PressedBack() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		result = true;
	}
	return result;
}

// Determine if the Left Thumb stick button is pressed down 
bool GamePad::XBoxController::PressedLeftThumb() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
		result = true;
	}
	return result;
}

// Determine if the Right Thumb stick button is pressed down
bool GamePad::XBoxController::PressedRightThumb() {

	// default result is false
	bool result = false;

	// Inspecting the controllerState
	if (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
		result = true;
	}
	return result;
}

// Determine the left trigger location
BYTE GamePad::XBoxController::LeftTriggerLocation() {

	// Initiate variable result to store data, initially 0
	BYTE result = 0;

	// if the left trigger is pass thresh hold set result to trigger level
	if (_controllerState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		result = _controllerState.Gamepad.bLeftTrigger;
	}
	return result;
}

// Determine the right trigger location
BYTE GamePad::XBoxController::RightTriggerLocation() {

	// Initiate variable result to store data, initially 0
	BYTE result = 0;

	// if the left trigger is pass thresh hold set result to trigger level
	if (_controllerState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		result = _controllerState.Gamepad.bRightTrigger;
	}
	return result;
}

// Determine the coordinate of left thumb stick
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {

	// Getting coordinate of right thumbstick
	float x = _controllerState.Gamepad.sThumbLX;
	float y = _controllerState.Gamepad.sThumbLY;

	// determine magnitude
	float mag = sqrt(x*x + y*y);

	// determine the direction
	float dirX = x / mag;
	float dirY = y / mag;

	// adjusted mag base on dead zone
	float adjustedMag = 0;

	//Dead Zone Radius
	unsigned int DZR;
	if (customDeadZone) {
		DZR = customDeadZoneRadius;
	}
	else {
		DZR = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}

	// if out of deadzone
	if (mag > DZR) {
		// if out of range
		// clip mag at 32767
		if (mag > 32767) {
			mag = 32767;
		}
		else {
			// otherwise readjust the mag respected to its expected range
			// giving a value from 0 to 32767
			mag = mag *((mag-DZR)/ (32767 - DZR));
		}
	}
	// if inside the dead zone set mag to 0
	else {
		mag = 0;
	}
	// Update new coordinate
	SHORT adjustedX = dirX * mag;
	SHORT adjustedY = dirY * mag;

	// Create new boject for right thumb stick coordinate
	GamePad::Coordinate lCoordinate(adjustedX, adjustedY);

	// return value of thumb stick after adjust for deadzone
	return lCoordinate;
}

// Determine the coordinate of the right thumb stick
GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {
	// Getting coordinate of right thumbstick
	float x = _controllerState.Gamepad.sThumbRX;
	float y = _controllerState.Gamepad.sThumbRY;

	// determine magnitude
	float mag = sqrt(x*x + y * y);

	// determine the direction
	float dirX = x / mag;
	float dirY = y / mag;

	// adjusted mag base on dead zone
	float adjustedMag = 0;

	//Dead Zone Radius
	unsigned int DZR;
	if (customDeadZone) {
		DZR = customDeadZoneRadius;
	}
	else {
		DZR = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	}

	// if out of deadzone
	if (mag > DZR) {
		// if out of range
		// clip mag at 32767
		if (mag > 32767) {
			mag = 32767;
		}
		else {
			// otherwise readjust the mag respected to its expected range
			// giving a value from 0 to 32767
			mag = mag * ((mag - DZR) / (32767 - DZR));
		}
	}
	// if inside the dead zone set mag to 0
	else {
		mag = 0;
	}
	
	// Update new coordinate
	SHORT adjustedX = dirX * mag;
	SHORT adjustedY = dirY * mag;

	// Create new boject for right thumb stick coordinate
	GamePad::Coordinate rCoordinate(adjustedX, adjustedY);

	// return value of thumb stick after adjust for deadzone
	return rCoordinate;
}

// Methods which set values that modify the behaviour of the controlle
// Setting vibration
void GamePad::XBoxController::Vibrate(WORD left, WORD right) {

	this->xinput = xinput;
	xinput->XInputGetState(_controllerId, &_controllerState);

	// Create a new vibration
	XINPUT_VIBRATION Vibration;

	// Allocate memory for new vibration
	memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

	// Making sure the value for vibration is in range
	// Writting vibration value out onto the Vibration state
	Vibration.wLeftMotorSpeed = left;
	Vibration.wRightMotorSpeed = right;

	// Vibrate the controller
	xinput->XInputSetState(_controllerId, &Vibration);

}

// Setting dead zone (Ignoring zone)
void GamePad::XBoxController::SetDeadzone(unsigned int radius) {
	customDeadZone = true;
	if (radius > 32766) {
		customDeadZoneRadius = 32766;
	}
	else {
		customDeadZoneRadius = radius;
	}
}