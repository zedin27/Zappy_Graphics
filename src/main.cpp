#include "zappy.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "FreeCamera.hpp"
#include "Player.hpp"
#include "SkyBox.hpp"
#include "Grid.hpp"
#include "Egg.hpp"
#include "FPSDisplay.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int	main(int argc, char *argv[])
{
	int	clientfd = open("testcommands", O_RDONLY);
	
	Window window(1600, 900, "zap");
	FreeCamera cam(window);
	Light light(glm::vec3(5, 10, -7), glm::vec3(1, 1, 1), 10);
	Map map(clientfd);
	Time clock;
	FPSDisplay fps;
	SkyBox sky("assets/textures/skybox/right.png",
		   "assets/textures/skybox/left.png",
		   "assets/textures/skybox/top.png",
		   "assets/textures/skybox/bottom.png",
		   "assets/textures/skybox/front.png",
		   "assets/textures/skybox/back.png");

	glClearColor(0.2, 0.25, 0.3, 1);
	while (!window.ShouldClose())
	{
		window.Clear();
		clock.Step();
		cam.Update();

		sky.Render(cam.Perspective());
		map.Render(cam.Perspective(), clock.Delta());

		fps.Render();
		window.Render();
	}	
	window.Close();
}
