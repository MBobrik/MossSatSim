#pragma once
#include "Math3D.h"

class LightSensor
{
	V3 direction;
	V3 aux_axis;
	double field_of_wiew;

	double intensity;
public:
	LightSensor( const V3&_direction, double _field_of_wiew ) : direction( Norm( _direction ) ), 
	aux_axis(MakeAuxAxis(_direction)),
	field_of_wiew( _field_of_wiew ), intensity( 0 ) {}
	LightSensor( const V3&_direction, double _field_of_wiew, const V3&_aux_axis ) : direction( Norm( _direction ) ), 
	aux_axis(_aux_axis),
	field_of_wiew( _field_of_wiew ), intensity( 0 ) {}

	// returns an unit vector that represents the direction the sensor is looking
	V3 GetDirection( ) const { return direction; }

	// returns an unit vector that represents the reference axis of the sensor fov. used for non-axis symmetric sensors
	V3 GetAuxAxis( ) const { return aux_axis; }

	// returns field of wiew of a sensor
	double GetFieldOfView( ) const { return field_of_wiew; }

	void SetIntensity( double _intensity ) { intensity = _intensity; }
	double GetIntensity( ) const { return intensity; }
};
