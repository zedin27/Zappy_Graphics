#pragma once

class	Character3D
{

	static ShadingProgram *_program;
	static bool _init;

	static std::vector<float> _square;
	
	static Gluint _squareID;
	static GLuint _UVID;
	static GLuint _textureID;
	static GLuint _textureLocationID;
	
public:
	Character3D(char c);
	~Character3D(void);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::vec3 position,
		       glm::vec3 color);
};
