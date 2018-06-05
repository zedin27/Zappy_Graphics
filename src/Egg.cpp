#include "Egg.hpp"

Egg::Egg(glm::vec2 pos) : _pos(pos), _hatched(false)
{
	_model = new Model("assets/egg.model");
}

Egg::~Egg(void)
{
	delete _model;
}

void	Egg::Crack(void)
{
	_hatched = true;
}

void	Egg::Render(std::pair<glm::mat4, glm::mat4> perspective)
{
	_model->Render(perspective, glm::mat4(1), glm::vec3(_pos.x, 0, _pos.y));
}
