#pragma once

#include "zappy.hpp"

class	Egg
{
	glm::vec2 _pos;
	bool _hatched;
public:
	Egg(glm::vec2 pos);
	~Egg(void);

	void	Crack(void);
};
