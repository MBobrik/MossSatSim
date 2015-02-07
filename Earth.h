#pragma once
#include "Math3D.h"

class Earth
{
	//TODO: add static and changing earth properties, rotation,
	// random albedo changes because of the clouds
	// magnetic field map and stuff
public:
	Earth( ) {}

	// resets to initial state
	void Reset( );

	// advances rotation and variable parameters by timestep dt
	void Timestep( double dt );
};