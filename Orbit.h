#pragma once
#include <math.h>
#include "Math3D.h"

class Orbit
{
	// orbital mechanics
	// LINK: http://biomathman.com/pair/ElementConversionRecipes.pdf
	
	// Primary elements
	
	double a; // Semimajor axis (a).
	double inc; // Inclination (i): Angle from equator to orbital plane.
	double O; // Longitude of ascending node (O): Angle from reference axis to ascending node. Void if inc=0.
	double e; // Eccentricity (e): ratio from semi-major axis to semi-minor axis. Circular if 0, non-orbit if >= 1
	double w; // Argument of periapsis (w): Angle from ascending node to periapsis.
	double M0; // initial mean anomaly M(0): initial Abstract angle at the beginning of the simulation. Radians. 

	// Derived elements
	double b; // Semiminor axis (b).
	double n; // Mean motion (n): Abstract angular velocity used to determine real angular velocity in an eccentric orbit. Radians per second.
	
	// Time dependent variables
	double M; // mean anomaly;
	double E; // eccentric anomaly
	
	// 3D position 
	V3 pos;

	void ComputePosFromElements();
	
	
public:
	// constants
	static double G; // Gravitational constant
	static double m; // Mass if the earth
	static double R; // Earth radius
	static double epsilon; // E algorithm precision

	Orbit(double _a, double _inc, double _O, double _e, double _w, double _M0 ) :
	a(_a),inc(_inc),O(_O), e(_e),w(_w), M0(fmod(_M0,2*PI)),
	b(a*sqrt(1-e*e)),
	n(sqrt((G*m)/(a*a*a))),
	M(M0), E(M0),pos() { ComputePosFromElements(); }

	// resets to initial state
	void Reset( );
	
	// advances orbit by timestep dt
	void Timestep( double dt );

	// returns position of the sat relative to the center of earth 
	V3 GetPosition() { return pos; }
};

class OrbitFromAP : public Orbit {
public:
	// initialize with perigee and apogee heights instead of semimajor axis and eccentricity
	OrbitFromAP(double _Pa, double _Aa, double _inc, double _O, double _w, double _M0) :
	Orbit(0.5 * (_Pa + _Aa) + R, _inc, _O, abs(_Pa - _Aa) / (_Pa + _Aa + 2 * R), _w, _M0) {}
};
