#include "LightComputer.h"

void LightComputer::ComputeSunshine( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::ComputeMoonshine( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::ComputeEarthshine( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::OccludeSunByMoon( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::OccludeSunByEarth( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::OccludeMoonByEarth( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::ComputeIntensity( LightSensor &sensor )
{
	intensity = 1;

	ComputeSunshine( sensor );
	ComputeMoonshine( sensor );
	ComputeEarthshine( sensor );
	OccludeSunByMoon( sensor );
	OccludeSunByEarth( sensor );
	OccludeMoonByEarth( sensor );

	//TODO: implement the rest of the computation

	sensor.SetIntensity( intensity );
}
