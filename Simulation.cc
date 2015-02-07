#include "Simulation.h"
#include "LightComputer.h"
#include "MagneticFieldComputer.h"

void Simulation::Reset()
{
	first_time = false;
	sun.Reset();
	moon.Reset();
	earth.Reset();
	orbit.Reset();
	sat.Reset();
	ctrl.Reset();

	sensors = ctrl.GetLightSensors();
	for(std::vector<LightSensor>::iterator i = sensors.begin(); i != sensors.end(); (i++)->SetIntensity( 0 ));
}

void Simulation::Timestep( double dt )
{
	if(first_time) { Reset(); }

	M3 rotation = sat.GetRotation();
	M3 inv_rotation = sat.GetInvRotation();

	V3 orbit_pos = orbit.GetPosition();

	LightComputer light_comp( rotation, orbit_pos, earth, sun, moon );

	for(std::vector<LightSensor>::iterator i = sensors.begin(); i != sensors.end(); i++)
	{
		i->SetIntensity( 0 );
		light_comp.ComputeIntensity( *i );
	}

	V3 B = MagneticFieldComputer( orbit_pos, earth ).ComputeMagneticField( );

	V3 W_rel = inv_rotation * sat.GetAngularVelocity();
	V3 B_rel = inv_rotation * B;

	V3 U_rel = ctrl.Process( dt, W_rel, B_rel, sensors );
	V3 U = rotation * U_rel;

	V3 torque = CrossProduct( U, B );
	sat.AddTorque( torque );

	sun.Timestep( dt );
	moon.Timestep( dt );
	earth.Timestep( dt );
	orbit.Timestep( dt );
	sat.Timestep( dt );
}
