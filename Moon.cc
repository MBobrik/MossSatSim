#include "Moon.h"

void Moon::Reset( )
{
}

void Moon::Timestep( double dt )
{
	//TODO: movement of the moon relative to earth... in case we realy need it
}

V3 Moon::GetPosition( )const
{
	//TODO: implement moon's movement first
	return V3( 0, -1, 0 );
}

double Moon::GetRadius( )const
{
	//TODO: implement moon's movement first
	return 0;
}
