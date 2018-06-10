#include "ResourceRenderer.hpp"

ResourceRenderer::ResourceRenderer(void)
{
	_models[0] = new Model("assets/resource0.model");
	_models[1] = new Model("assets/resource1.model");
	_models[2] = new Model("assets/resource2.model");
	_models[3] = new Model("assets/resource3.model");
	_models[4] = new Model("assets/resource4.model");
	_models[5] = new Model("assets/resource5.model");
	_models[6] = new Model("assets/resource6.model");
}

void	ResourceRenderer::Render(std::pair<glm::mat4, glm::mat4> perspective,
				 glm::vec2 pos,
				 const std::vector<int>& resources)
{
	for (size_t i = 0; i < 7; i++)
	{
		if (resources[i] == 0)
			continue;
		glm::mat3 transform(1);
		transform[1][1] = 1 + 0.2 * resources[i];
		_models[i]->Render(perspective,
				  glm::mat4(transform),
				  glm::vec3(pos.x, 0, -pos.y));
	}
}
