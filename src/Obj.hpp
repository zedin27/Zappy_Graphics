#pragma once

class	Obj
{
	static ShadingProgram _normalProgram;
	static ShadingProgram _outlineProgram;
	static ShadingProgram _cartoonProgram;
	static bool _init;
	
	ObjFileArrayExtractor _extractor;
	Texture _textureParser;
	
	GLuint _uvArrayID;
	GLuint _normalArrayID;
	GLuint _vertexArrayID;
	
	static	GLuint _projectionID_normal;
	static	GLuint _transformID_normal;
	static	GLuint _textureLocationID_normal;
	
	static	GLuint _lightPosID_normal;
	static	GLuint _lightColorID_normal;
	static	GLuint _lightFalloffID_normal;
	static	GLuint _lightNumID_normal;
	static	GLuint _materialID_normal;
	
	
	static	GLuint _projectionID_cartoon;
	static	GLuint _transformID_cartoon;
	static	GLuint _textureLocationID_cartoon;

	static	GLuint _projectionID_outline;
	static	GLuint _transformID_outline;
	
	GLuint _textureID;
	
	GLuint _lightPosID;
	GLuint _lightColorID;
	GLuint _lightFalloffID;
	GLuint _lightNumID;
	
public:

	static const glm::vec3 noOutline;
	static const std::vector<glm::vec3> noOutlines;
	static const std::vector<float> noSize;
	
	Obj(std::string filepath,
	    std::string texturePath,
	    float specular = 1,
	    float diffuse = 1,
	    float fog = 1000000,
	    glm::vec3 fogcol = glm::vec3(0));
	~Obj(void);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::mat4 transform,
		       glm::vec3 outlineColor = noOutline,
		       float outlineSize = 0.1,
		       bool cartoon = false);
	
	void	RenderInstanced(std::pair<glm::mat4, glm::mat4> perspective,
				std::vector<glm::mat4> transforms,
				std::vector<glm::vec3> outlineColors = noOutlines,
				std::vector<float> outlineSize = noSize);
};
