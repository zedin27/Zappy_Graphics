#pragma once

#include "ShadingProgram.hpp"
#include "zappy.hpp"
#include "Text.hpp"

#define CHAR3D_VERTEX_SHADER_PATH "src/shaders/3DCharVertex.glsl"
#define CHAR3D_FRAG_SHADER_PATH "src/shaders/3DCharFrag.glsl"

class	Character3D
{

	static ShadingProgram *_program;
	static bool _init;

	static std::vector<float> _square;
	static std::vector<float> _uv;

	static GLuint _squareID;
	static GLuint _UVID;
	static GLuint _textureID;
	static GLuint _textureLocationID;
	static GLuint _projectionID;
	static GLuint _lookAtID;
	static GLuint _positionID;
	static GLuint _sizeID;
	static GLuint _colorID;

public:
	Character3D(void);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::vec3 position,
		       glm::vec3 color,
		       float size,
		       char c);
};
