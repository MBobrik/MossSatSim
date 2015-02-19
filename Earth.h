#pragma once
#include "Math3D.h"

class Earth
{
	//TODO: add static and changing earth properties, rotation,
	// random albedo changes because of the clouds
	// magnetic field map and stuff
public:
	
	static double R; // Earth radius
	static double Hatm; // scaled atmosphere size
	static double Twilight; // half-occlusion point
	static double HorizonRefraction; // refraction at horizon
	
	Earth( ) {}

	// resets to initial state
	void Reset( );

	// advances rotation and variable parameters by timestep dt
	void Timestep( double dt );
	
	double GetAtmRadiusLo() const { return R; }
	double GetAtmRadiusHi() const { return R+Hatm; }
	double GetMaxRefractionAngle() const { return HorizonRefraction; }
	double GetTwilight() const { return Twilight; }
};
