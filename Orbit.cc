#include "Orbit.h"

double Orbit::G = 6.67384e-11; // Gravitational constant
double Orbit::m = 5.97219e24; // Mass if the earth
double Orbit::R = 6.371e6; // Earth radius
double Orbit::epsilon = 8e-31; // E algorithm precision

void Orbit::ComputePosFromElements( )
{
	if(fabs(E-M) >= PI ) { // previous E is worthless, recompute from scratch
		E = M;
	}

	for(double d;;) {
		d = E - e * sin(E) - M;
		if( d*d < epsilon ) { // d*d is faster than fabs(d)
			break;
		}
		E -= d / (1-e*cos(E) ); 
	}

	V3 Xdir(   cos(O) * cos(w) - sin(O) * cos(inc) * sin(w),
			   sin(O) * cos(w) + cos(O) * cos(inc) * sin(w), 
											 sin(inc) * sin(w ) );

	V3 Ydir( - cos(O) * sin(w) - sin(O) * cos(inc) * cos(w),
			 - sin(O) * sin(w) + cos(O) * cos(inc) * cos(w), 
											 sin(inc) * cos(w ) );

	pos = Xdir * a * cos(E) + Ydir * b * sin(E); 
}


void Orbit::Reset( )
{
	M = M0; E=M0; 
	ComputePosFromElements();
}

void Orbit::Timestep( double dt )
{
	M += dt * n;
	if( M >= 2 * PI ) { // next orbit - we renormalize M and E
		double orb = 2*PI * floor(M/(2*PI));
		M -= orb;
		E -= orb;
	}
	
	ComputePosFromElements();
}

