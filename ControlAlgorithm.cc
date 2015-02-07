#include "ControlAlgorithm.h"

ControlAlgorithm::ControlAlgorithm() {}


// resets the algorithm to initial state
void ControlAlgorithm::Reset()
{
}

std::vector<LightSensor> ControlAlgorithm::GetLightSensors()
{

	// need more sensors ? just add
	std::vector<LightSensor> sensors = {
		LightSensor(V3(-1, 0, 0), Deg2Rad(90)),
		LightSensor(V3(1, 0, 0), Deg2Rad(90)),
		LightSensor(V3(0, -1, 0), Deg2Rad(90)),
		LightSensor(V3(0, 1, 0), Deg2Rad(90)),
		LightSensor(V3(0, 0, -1), Deg2Rad(90)),
		LightSensor(V3(0, 0, 1), Deg2Rad(90)),
	};

	return sensors;
}

V3 ControlAlgorithm::Process(double timestep, const V3 &angular_velocity, const V3 &magnetic_field, const std::vector<LightSensor> &light_intensities)
{
	//TODO: the algorithm
	return V3(1, 1, 1);
}
