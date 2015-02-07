#include "Math3D.h"
#include "LightSensor.h"
#include <vector>

class ControlAlgorithm
{
	//TODO: the algorithm, duh !
public:
	ControlAlgorithm();

	// resets the algorithm to initial state
	void Reset( );

	// initializes a vector od sat's light sensors, will be called once at the beginning
	std::vector<LightSensor> GetLightSensors();

	// output is the magnetotorquer signal strength as a fraction of the GetMaxTorquerMomentum() value
	V3 Process(double timestep, const V3 &angular_velocity, const V3 &magnetic_field, const std::vector<LightSensor> &light_intensities);
};