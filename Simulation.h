#pragma once

#include "Math3D.h"
#include "Sun.h"
#include "Moon.h"
#include "Earth.h"
#include "Orbit.h"
#include "LightSensor.h"
#include "SatPhysics.h"
#include "ControlAlgorithm.h"
#include <vector>

class Simulation
{
	Sun &sun;
	Moon &moon;
	Earth &earth;
	Orbit &orbit;
	SatPhysics &sat;
	ControlAlgorithm &ctrl;

	bool first_time;

	std::vector<LightSensor> sensors;

public:
	Simulation(
		Sun &_sun, Moon &_moon, Earth &_earth,
		Orbit &_orbit, SatPhysics &_sat,
		ControlAlgorithm &_ctrl ) :
		sun( _sun ), moon( _moon ), earth( _earth ),
		orbit( _orbit ), sat( _sat ),
		ctrl( _ctrl ),
		first_time( true ), sensors() {}

	void Reset();

	void Timestep( double dt );
};
