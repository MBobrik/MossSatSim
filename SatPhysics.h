#pragma once
#include "Math3D.h"

class SatPhysics
{
	V3 torquer_strength;

	Q initial_rotation;
	V3 initial_angular_velocity;

	Q rotation;
	V3 angular_velocity;
	M3 inertia_momentum;
	M3 inverse_inertia_momentum; // inverse inertia momentum

	V3 torque;

public:

	SatPhysics( const Q &_rotation, const V3 &_angular_velocity, const M3 _inertia_momentum, const V3 &_torquer_strength ) :
		torquer_strength( _torquer_strength ),
		initial_rotation( _rotation ), initial_angular_velocity( _angular_velocity ),
		rotation( _rotation ), angular_velocity( _angular_velocity ), 
		inertia_momentum( _inertia_momentum ), inverse_inertia_momentum( !_inertia_momentum ),
		torque()
	{}

	// resets to initial state
	void Reset( );

	// magnetotorquer coil strengths X,Y,Z components
	V3 GetMaxTorquerMomentum() { return torquer_strength; }

	// adds torque acting through the next timestep - you can call it multiple times to sum up different torques
	void AddTorque( const V3 &_torque ) { torque += _torque; }

	// advances rotation by timestep dt
	void Timestep( double dt );

	// get actual rotation matrix
	M3 GetRotation() { return rotation; }
	// get inverse rotation matrix
	M3 GetInvRotation( ) { return -rotation; }

	// get angular velocity
	V3 GetAngularVelocity() { return angular_velocity; }
};