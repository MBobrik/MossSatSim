#include "Orbit.h"
// We need to define pi, radius, mass, and gravitational constant!

void Orbit::Reset( )
{
}

void Orbit::Timestep( double dt )
{
	//TODO: all orbital mechanics !
	
	// How are we going to convert keplerian elements to cartesian coordinates and orbital propagation calculations?
		// This is a pdf that tells how to do that, the question remains of whether this will be computationally efficient or not.
		// LINK: http://biomathman.com/pair/ElementConversionRecipes.pdf
	
	// Keplerian Elements (double precision)
	
	// Primary elements
	double a; // Semimajor axis (a).
	double inc; // Inclination (i): Angle from equator to orbital plane.
	double O; // Longitude of ascending node (O): Angle from reference axis to ascending node. Void if inc=0.
	double e; // Eccentricity (e): ratio from semi-major axis to semi-minor axis. Circular if 0, non-orbit if >= 1
	double w; // Argument of periapsis (w): Angle from ascending node to periapsis.
	double f; // True anomaly (f): Angle from periapsis to satellite position.
	
	// Secondary elements (computed from primary elements)
	double E = ftoE(this=>e, this=>f); // Eccentric anomaly
	double M = EtoM(this=>e, this=>E); // Mean anomaly (M): Abstract angle used to determine mean motion and real angular velocity in an eccentric orbit. update M += ((this=>n)*t)
	double n = sqrt((G*M)/((this=>a)^3)); // Mean motion (n): Abstract angular velocity used to determine real angular velocity in an eccentric orbit. Radians per second.
	double T = 2*PI*sqrt(((this=>a)^3)/(G*M)); // Sidereal orbital period.
	double A = ((this=>a)*(1-((this=>e)^2)))/(1+(this=>e)*cos(this=>f)); // Altitude from center of Earth. Dependent on a, e, and f. Possible to use T if a is unknown.
	double V = sqrt(G*M((2/r)-(1/(this->a)))); // Linear velocity Vis-viva equation.
	
	// Conversion functions (code adapted from OrbitNerd's, youtube)

	double ftoE (double e, double f) {
		// True anomaly to eccentric anomaly.
		double sinE = sin(f)*sqrt(1-e^2)/(1+e*cos(f));
		double cosE = (e+cos(f))/(1+e*cos(f));
		return atan2(double sinE, double cosE);
	}

	double EtoM(double e, double E) {
		// Eccentric anomaly to mean anomaly.
		return E-e*sin(E);
	}

	double MtoE(double e, double M) {
		// Mean anomaly to eccentric anomaly

		// Make sure M lies between -pi and pi
		M = fmod(double M, double pi);
		if (M < pi) {M = M + 2*pi;}
		else if (M > pi) {M = M - 2*pi;}

		if ((M > -pi && M < 0) || (M > pi)) {E = M - e;}
		else E = M + e;

		// Iteratively approach value of E until it is more precise than our standards (defined by variable zero)
		double Enew = E;
		double zero = 1E-16; // Will this output a 16 decimal number or a 17 decimal number? I need 16,
		do {
			E = Enew;
			Enew = E + (M - E + e*sin(E))/(1 - e*cos(E));
		} while (abs(Enew - E) > zero)
	
		return Enew;
		}

	double Etof (double e, double E) {
		// Eccentric anomaly to true anomaly.
		double sinf = sin(E)*sqrt(1-e^2)/(1-e*cos(E));
		double cosf = (cos(E)-e)/(1-e*cos(E));
		return atan2(double sinf, double cosf);
	}
}


V3 Orbit::GetPosition( )
{
	//TODO: implement orbiting first !
	return V3( 0, 1, 0 );
}
