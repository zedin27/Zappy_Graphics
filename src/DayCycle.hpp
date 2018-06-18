#pragma once

#include "zappy.hpp"
#include "Light.hpp"

class	DayCycle
{	

	double _timestep;
	Light *_sun;
	
public:
	DayCycle(void);
	~DayCycle(void);

	void	Update(double dt);
};
