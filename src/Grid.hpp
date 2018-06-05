#pragma once

#include "zappy.hpp"
#include "Model.hpp"

class	Grid
{
	int _x;
	int _y;
	Model *_model;
public:
	Grid(int x, int y);
	~Grid(void);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective);
};
