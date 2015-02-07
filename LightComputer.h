#pragma once
#include "Math3D.h"
#include "Sun.h"
#include "Earth.h"
#include "Moon.h"
#include "LightSensor.h"

class LightComputer
{
	double intensity;

	M3 rotation;
	V3 earth_rel_pos;
	const Earth &earth;
	const Sun &sun;
	const Moon &moon;

	//TODO: write the light intensity computation

	void ComputeSunshine( const LightSensor &sensor );
	void ComputeMoonshine( const LightSensor &sensor );
	void ComputeEarthshine( const LightSensor &sensor );

	void OccludeSunByMoon( const LightSensor &sensor );
	void OccludeSunByEarth( const LightSensor &sensor );
	void OccludeMoonByEarth( const LightSensor &sensor );

public:
	LightComputer( const M3 &_rotation, const V3 &_earth_rel_pos,
		const Earth &_earth, const Sun &_sun, const Moon &_moon ) : intensity(0), rotation( _rotation ), earth_rel_pos( _earth_rel_pos ),
		earth( _earth ), sun( _sun ), moon( _moon )	{}

	//TODO: write the light intensity computation
	void ComputeIntensity( LightSensor &sensor );
};