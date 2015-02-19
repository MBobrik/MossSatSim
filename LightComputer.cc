#include "LightComputer.h"
#include "MathFunctions.h"


void LightComputer::ComputeSunshine( const LightSensor &sensor )
{
	double sun_size =sun.GetAngularSize(); 

	double cos_sun_angle = Dot(sun.GetDirection(), sensor_dir);
	double sun_angle = acos( cos_sun_angle );
	
	double border_angle = sun_angle + 0.5 * sun_size - sensor.GetFieldOfView();
	
	// we are not going to integrate the luminosity of the exact part inside sensor fov,
	// thus just a smooth decrease as the sun moves out of the fov
	sun_intensity = cos_sun_angle * InterpolateSmooth01(1-border_angle/sun_size);
}

void LightComputer::ComputeMoonshine( const LightSensor &sensor )
{
	//TODO: implement
}

double LightComputer::RaytraceEarthshine( const V3 &ray ) {
	return 0; //TODO: implement
}

int LightComputer::RayRaster = 1.0 / 16.0; // raycast rastering grid

void LightComputer::ComputeEarthshine( const LightSensor &sensor )
{
	//TODO: implement the raytracing function
	
	// earthshine is on one hand the biggest confounding factor
	// and on the other hand the main information source about where the earth actually is
	// so we do it the hard way - raytracing
	
	double fov = 0.5 * sensor.GetFieldOfView();
	double sum = 0,cnt = 0;
	
	for( double y = -1 ; y <= 1 + 0.5 * RayRaster ; y += RayRaster ) {
		for( double x = -1 ; x <= 1 + 0.5 * RayRaster ; x += RayRaster ) {
			
			double r2 = x*x+y*y;
			
			if(r2>1) { continue; } // circular aperture
			
			// linearize and stretch the ray grid over fov
			double r = sqrt(r2);
			double f = tan(fov*r);
			double scl = 1.0/sqrt( 1 + f*f ) ;
			double scl_xy = scl * f / r;
			
			sum += RaytraceEarthshine( sensor_dir * scl + sensor_aux * (x*scl_xy) + sensor_up * (y*scl_xy) );
			cnt += 1;
		}
	}
	
	earth_intensity = sum / cnt;
}

void LightComputer::OccludeSunByMoon( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::OccludeSunByEarth( const LightSensor &sensor )
{
	double earth_dist = earth_rel_pos.Sz();
	double sun_size =sun.GetAngularSize(); 
	double atm_size_lo = acos( earth.GetAtmRadiusLo() / earth_dist) - 0.5 * sun_size - earth.GetMaxRefractionAngle();
	double atm_size_hi = acos( earth.GetAtmRadiusHi() / earth_dist) + 0.5 * sun_size;
	double earth_angle = acos( Dot(earth_rel_pos,sun.GetDirection()) / earth_dist );
	
	double atm_rel_angle = earth_angle - atm_size_lo;
	double atm_max_angle = atm_size_hi - atm_size_lo;
	
	// we are not going to raytrace through the atmosphere
	// just a smooth function that starts to fall as the sun's border touches the fringe of the atmosphere
	// falls to half at an arbitrary twilight point
	// and smoothly falls to zero as the sun is completely obstructed by the Earth's body
	sun_intensity *= InterpolateSmoothTHalf( earth.GetTwilight(), atm_rel_angle / atm_max_angle );
}

void LightComputer::OccludeMoonByEarth( const LightSensor &sensor )
{
	//TODO: implement
}

void LightComputer::ComputeIntensity( LightSensor &sensor )
{
	sun_intensity = earth_intensity = moon_intensity = 0;
	sensor_dir = Norm( rotation * sensor.GetDirection() );
	sensor_aux = Norm( rotation * sensor.GetAuxAxis() );
	sensor_up = Cross(sensor_dir,sensor_aux);

	ComputeSunshine( sensor );
	ComputeMoonshine( sensor );
	ComputeEarthshine( sensor );
	OccludeSunByMoon( sensor );
	OccludeSunByEarth( sensor );
	OccludeMoonByEarth( sensor );

	//TODO: implement the rest of the computation

	sensor.SetIntensity( sun_intensity + earth_intensity + moon_intensity );
}
