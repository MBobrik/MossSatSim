#pragma once
#include "Math3D.h"
#include "Earth.h"

class MagneticFieldComputer
{
	V3 earth_rel_pos;
	const Earth &earth;

	//TODO: write the magnetic field computation
public:
	MagneticFieldComputer(const V3 &_earth_rel_pos, const Earth &_earth ) : earth_rel_pos( _earth_rel_pos ), earth( _earth )
	{}

	V3 ComputeMagneticField();
};