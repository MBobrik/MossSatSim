#pragma once
#include "Math3D.h"

class Sun
{
	//TODO: real sun movement across the sky during a year
public:
	Sun( ) {}

	// resets to initial state
	void Reset( );

	// advances sun position by timestep dt
	void Timestep( double dt );

	// returns an unit vector that represents the direction towards the sun
	V3 GetDirection( ) const;

	// returns angular size of the sun disc
	double GetAngularSize( ) const;
};