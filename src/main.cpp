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
	Player p1(glm::vec2(0, 0), glm::vec2(0, 1), "p1", 1, 1);
	Player p2(glm::vec2(0, 0), glm::vec2(1, 0), "p2", 2, 1);
	Light light(glm::vec3(1000, 1000, 0), glm::vec3(1, 1, 1), 100000);
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

	glm::vec2 positions[2] = {{0, 0}, {3, 9}};
	
	while (!window.ShouldClose())
	{
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		window.Clear();
		clock.Step();
		p1.Update(clock.Delta());
		p2.Update(clock.Delta());

		size_t t1 = clock.Total() / 5;
		size_t t2 = clock.Total() / 7;
		
		p1.MoveTo(positions[t1 % 2]);
		p2.MoveTo(positions[t2 % 2]);
		
		cam.Update();
		sky.Render(cam.Perspective());
		grid.Render(cam.Perspective());
		egg.Render(cam.Perspective());
		p1.Render(cam.Perspective());
		p2.Render(cam.Perspective());
		
		window.Render();
	}
	window.Close();
}
