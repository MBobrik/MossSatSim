#include "SatPhysics.h"

void SatPhysics::Reset()
{
	rotation = initial_rotation;
	angular_velocity = initial_angular_velocity;
	torque = V3( 0, 0, 0 );
}

void SatPhysics::Timestep( double dt )
{
	// basic integration here ... a more sophisticated numerical method will be added later

	M3 R = rotation, IR = -rotation;
	M3 Iact = R * inertia_momentum * IR;
	M3 IIact = IR * inverse_inertia_momentum * R;
	V3 dw = IIact * ( torque + CrossProduct( Iact*angular_velocity, angular_velocity ) );

	torque = V3( 0, 0, 0 );

	angular_velocity += dw * dt;

	rotation = QAngle( angular_velocity, angular_velocity.Sz( ) * dt ) * rotation;
}
