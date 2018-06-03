#include "Egg.hpp"

Egg::Egg(glm::vec2 pos) : _pos(pos), _hatched(false)
{

}

Egg::~Egg(void)
{
}

void	Egg::Crack(void)
{
	_hatched = true;
}
