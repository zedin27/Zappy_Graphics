#include "zappy.hpp"
#include "Window.hpp"
#include "FreeCamera.hpp"
#include "Player.hpp"
#include "SkyBox.hpp"
#include "Grid.hpp"
#include "Egg.hpp"

int	main(void)
{
	Window window(1600, 900, "zap");
	FreeCamera cam(window);
	Player p1(glm::vec2(9, 9), glm::vec2(0, 1), "p1", 1, 1, glm::vec2(10, 10));
	Light light(glm::vec3(5, 5, -5), glm::vec3(1, 1, 1), 5);
	Time clock;
	SkyBox sky("assets/textures/skybox/right.png",
		   "assets/textures/skybox/left.png",
		   "assets/textures/skybox/top.png",
		   "assets/textures/skybox/bottom.png",
		   "assets/textures/skybox/front.png",
		   "assets/textures/skybox/back.png");
	Grid grid(10, 10);
	Egg egg(glm::vec2(2, 2));
	
	glClearColor(0.2, 0.25, 0.3, 1);

	glm::vec2 positions[4] = {{9, 9}, {9, 0}, {0, 0}, {0, 9}};
	glm::vec2 directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	
	while (!window.ShouldClose())
	{
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		window.Clear();
		clock.Step();
		
		p1.Update(clock.Delta());

		int index1 = clock.Total() / 4.0f;
		int index2 = clock.Total() / 4.0f + 0.5f;
		index1 %= 4;
		index2 %= 4;

		p1.SetDir(directions[index1]);
		p1.MoveTo(positions[index2]);
		
		cam.Update();
		sky.Render(cam.Perspective());
		grid.Render(cam.Perspective());
		egg.Render(cam.Perspective());
		p1.Render(cam.Perspective());
		
		window.Render();
	}
	window.Close();
}
