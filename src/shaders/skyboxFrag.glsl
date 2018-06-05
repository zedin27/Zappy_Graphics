#version 410 core

in vec3 texCoor;

out vec4 color;

uniform samplerCube tex;

void	main()
{
	color = texture(tex, texCoor);
}