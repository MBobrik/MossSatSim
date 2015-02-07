#include "Sun.h"

void Sun::Reset( )
{
}

void Sun::Timestep( double dt )
{
	//TODO: all yearly sun movement across the celestial sphere !
}

V3 Sun::GetDirection( ) const
{
	//TODO: implement sun's movement first
	return V3( 1, 0, 0 );
}

double Sun::GetAngularSize( ) const
{
	//TODO: implement sun's movement first
	return 0;
}
