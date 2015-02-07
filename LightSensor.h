#pragma once
#include "Math3D.h"

class LightSensor
{
	V3 direction;
	double field_of_wiew;

	double intensity;
	//TODO: more realistic properties of a light sensor
public:
	LightSensor( const V3&_direction, double _field_of_wiew ) : direction( Norm( _direction ) ), field_of_wiew( _field_of_wiew ), intensity( 0 ) {}

	// returns an unit vector that represents the direction the sensor is looking
	V3 GetDirection( ) const { return direction; }

	// returns field of wiew of a sensor
	double GetFieldOfView( ) const { return field_of_wiew; }

	void SetIntensity( double _intensity ) { intensity = _intensity; }
	double GetIntensity( ) const { return intensity; }
};