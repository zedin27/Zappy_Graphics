#include "zappy.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "FreeCamera.hpp"
#include "Player.hpp"
#include "SkyBox.hpp"
#include "Grid.hpp"
#include "Egg.hpp"

#include <fcntl.h>

int	main(void)
{
	int fd = open("test", O_RDONLY);
		
	Window window(1600, 900, "zap");
	FreeCamera cam(window);
	Light light(glm::vec3(1000, 1000, 0), glm::vec3(1, 1, 1), 1000000);
	Map map(fd, glm::vec2(10, 10));
	Time clock;

	glClearColor(0.2, 0.25, 0.3, 1);

	while (!window.ShouldClose())
	{
		window.Clear();
		clock.Step();
		cam.Update();

		map.Render(cam.Perspective(), clock.Delta());
		
		window.Render();
	}	
	window.Close();
}
