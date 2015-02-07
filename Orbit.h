#pragma once
#include "Math3D.h"

class Orbit
{
	//TODO: real orbital parameters
public:
	Orbit() {}

	// resets to initial state
	void Reset( );

	// advances orbit by timestep dt
	void Timestep( double dt );

	// returns relative position of the center of earth to the sat
	V3 GetPosition();
};