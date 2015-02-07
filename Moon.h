#pragma once
#include "Math3D.h"

class Moon
{
	//TODO: we won't normally need to implement it
	// it's light is too weak, and sun eclipses too rare and short
	// but in case we have too much time on our hands...
public:
	Moon( ) {}

	// resets to initial state
	void Reset( );

	// advances moon position by timestep dt
	void Timestep( double dt );

	// returns a relative position of the moon to earth center
	V3 GetPosition( ) const;

	// returns moon's radius
	double GetRadius( ) const;
};