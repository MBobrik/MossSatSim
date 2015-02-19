#pragma once
#include "Math3D.h"
#include "Sun.h"
#include "Earth.h"
#include "Moon.h"
#include "LightSensor.h"

class LightComputer
{
	double sun_intensity;
	double earth_intensity;
	double moon_intensity;

	V3 sensor_dir;
	V3 sensor_aux;
	V3 sensor_up;

	M3 rotation;
	V3 earth_rel_pos; // this is the position of the center of the earth relative to sat ! not orbit position
	const Earth &earth;
	const Sun &sun;
	const Moon &moon;
	
	static int RayRaster;

	//TODO: write the light intensity computation
	double RaytraceEarthshine( const V3 &ray );
	
	void ComputeSunshine( const LightSensor &sensor );
	void ComputeMoonshine( const LightSensor &sensor ); //TODO: implement
	void ComputeEarthshine( const LightSensor &sensor ); //TODO: implement raytrace

	void OccludeSunByMoon( const LightSensor &sensor ); //TODO: implement
	void OccludeSunByEarth( const LightSensor &sensor );
	void OccludeMoonByEarth( const LightSensor &sensor ); //TODO: implement

public:
	LightComputer( const M3 &_rotation, const V3 &_orbit_pos,
		const Earth &_earth, const Sun &_sun, const Moon &_moon ) : 
			sun_intensity(0), earth_intensity(0), moon_intensity(0), 
			rotation( _rotation ), earth_rel_pos( -_orbit_pos ),
		earth( _earth ), sun( _sun ), moon( _moon )	{}

	void ComputeIntensity( LightSensor &sensor ); //TODO: implement the sub
};
