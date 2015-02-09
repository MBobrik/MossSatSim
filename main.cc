#include "Simulation.h"
#include "RandomGen.h"
#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>

using namespace std;

V3 RndSphere( Rnd &rnd )
{
	for(;;)
	{
		V3 r( rnd.Drand(), rnd.Drand(), rnd.Drand() );
		if(r.Sz2() < 1) { return r; }
	}
	return V3(); // never
}

Q RndQuat( Rnd &rnd )
{
	V3 r = RndSphere( rnd );
	return Q( r, sqrt( 1 - r.Sz2() ) );
}

int main()
{
	Rnd rnd( 1701 ); // arbitrary seed

	Sun sun;
	Moon moon;
	Earth earth;
	OrbitFromAP orbit(407000, 399000, Deg2Rad(51.6480), Deg2Rad(3.6517), Deg2Rad(346.4218), Deg2Rad(119.6532) ); // ISS @ Epoch 09 February 2015 02:33:02 UTC

	SatPhysics sat(
		QAngle( 0, 0, 1, 0 ),  // some arbitrary val
		V3( 0, Deg2Rad( 5 ), Deg2Rad( 22 ) ), // some arbitrary val
		M3( 0.001, 0, 0, 0, 0.001, 0, 0, 0, 0.002  ), // TODO: real value
		V3( 0.2, 0.2, 0.2 ) // TODO: real value
		);

	ControlAlgorithm ctrl;

	Simulation sim( sun, moon, earth, orbit, sat, ctrl );

	ofstream fstr;
	fstr.open( "result.txt" );

	for(int i = 0; i < 20000; i++)
	{
		if (!(i % 10000)) { cout << '\n'; }
		if (!(i % 200)) { cout << '.'; }

		V3 sun_dir = sun.GetDirection();

		V3 angular_velocity = sat.GetAngularVelocity();

		double rpm = 30 / PI * angular_velocity.Sz();

		double sun_rot_angle = Rad2Deg( Angle( sun_dir, angular_velocity ) );

		V3 sat_axis = sat.GetRotation() * V3( 0, 0, 1 );

		double axis_rot_angle = Rad2Deg( Angle( sat_axis, angular_velocity ) );

		fstr << "RPM : " << setw(7) << setprecision( 3 ) << rpm << 
				" Rot2Sun angle : " << setw( 10 ) << setprecision( 6 ) << sun_rot_angle << 
				" Rot2Sat angle : " << setw( 10 ) << setprecision( 6 ) << axis_rot_angle << '\n';

		if (!((i+1) % 200)) {
			V3 pos = orbit.GetPosition();
			fstr << "POS : (" << setw(15) << setprecision(3) << fixed << pos.x << ',' << setw(15) << pos.y << ',' << setw(15) << pos.z << ")\n";
		}

		sim.Timestep( 0.05 );
	}

	fstr.close();

	return 0;
}