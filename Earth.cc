#include "Earth.h"

double Earth::R = 6.371e6; // Earth radius
double Earth::Hatm = 30e3; // // scaled atmosphere size
double Earth::Twilight = 0.1; // half-occlusion point
double Earth::HorizonRefraction = Deg2Rad(0.59); // refraction at horizon

void Earth::Reset()
{
}

void Earth::Timestep( double dt )
{
	//TODO: vary all the properties by earth rotation
	// and some random factors simulating albedo changes due weather and seasons
	// and magnetic field changes due to geomagnetic events
}
