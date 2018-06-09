#include "zappy.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "FreeCamera.hpp"
#include "Player.hpp"
#include "SkyBox.hpp"
#include "Grid.hpp"
#include "Egg.hpp"
#include "FPSDisplay.hpp"
#include "Obj.hpp"

#include <fcntl.h>

int	main(void)
{
	int fd = open("test", O_RDONLY);
		
	Window window(1600, 900, "zap");
	FreeCamera cam(window);
	Light light(glm::vec3(500, 1000, 0), glm::vec3(1, 1, 1), 1000000);
	Map map(fd, glm::vec2(25, 25));
	Time clock;
	FPSDisplay fps;
	SkyBox sky("assets/textures/skybox/right.png",
		   "assets/textures/skybox/left.png",
		   "assets/textures/skybox/top.png",
		   "assets/textures/skybox/bottom.png",
		   "assets/textures/skybox/front.png",
		   "assets/textures/skybox/back.png");

//	Obj obj("assets/meshes/fullface.obj", "assets/textures/white.png");

	glClearColor(0.2, 0.25, 0.3, 1);

	while (!window.ShouldClose())
	{
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		
		window.Clear();
		clock.Step();
		cam.Update();

		sky.Render(cam.Perspective());
//		obj.Render(cam.Perspective(), glm::mat4(1), glm::vec3(0, 0, 0), 0.005, false);
		
		map.Render(cam.Perspective(), clock.Delta());

		fps.Render();
		window.Render();
	}	
	window.Close();
}
