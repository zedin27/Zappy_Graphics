#include "DayCycle.hpp"

DayCycle::DayCycle(void)
{
	_timestep = 0;
	_sun = new Light(glm::vec3(1000 * sin(_timestep), 1000 * cos(_timestep), 0), glm::vec3(1, 1, 1), 1000);
}

DayCycle::~DayCycle(void)
{
	delete _sun;
}

void	DayCycle::Update(double dt)
{
	_timestep += dt * 0.1;	
	delete _sun;

	_sun = new Light(glm::vec3(1000 * sin(_timestep), 1000 * cos(_timestep), 0),
			 glm::vec3(3 * std::max(cos(_timestep), 0.0),
				   3 * std::max(cos(_timestep), 0.0),
				   3 * std::max(cos(_timestep), 0.0)),
			 1000);
}
