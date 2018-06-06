#include "Grid.hpp"

Grid::Grid(int x, int y) : _x(x), _y(y)
{
	_model = new Model("assets/block.model");
}

Grid::~Grid(void)
{
	delete _model;
}

void	Grid::Render(std::pair<glm::mat4, glm::mat4> perspective)
{
	for (int x = 0; x < _x; x++)
	{
		for (int y = 0; y < _y; y++)
		{
			_model->Render(perspective, glm::mat4(1), glm::vec3(x, -1, -y));
		}
	}
}
