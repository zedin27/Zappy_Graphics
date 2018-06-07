#include "Obj.hpp"

ShadingProgram Obj::_normalProgram(STANDARD_OBJ_VERTEX, "", STANDARD_OBJ_FRAG);
ShadingProgram Obj::_cartoonProgram(STANDARD_OBJ_VERTEX, "", CARTOON_OBJ_FRAG);
ShadingProgram Obj::_outlineProgram(OUTLINE_OBJ_VERTEX, "", OUTLINE_OBJ_FRAG);
bool	Obj::_init = false;

GLuint Obj::_projectionID_normal;
GLuint Obj::_transformID_normal;
GLuint Obj::_textureLocationID_normal;

GLuint Obj::_projectionID_cartoon;
GLuint Obj::_transformID_cartoon;
GLuint Obj::_textureLocationID_cartoon;

GLuint Obj::_projectionID_outline;
GLuint Obj::_transformID_outline;

Obj::Obj(std::string filePath,
	 std::string texturePath,
	 float specular,
	 float diffuse,
	 float fog,
	 glm::vec3 fogcol) :
_extractor(filePath),
_textureParser(texturePath)
{
	if (!_init)
	{
		_projectionID_normal = glGetUniformLocation(_normalProgram.ID(), "projection");
		_transformID_normal = glGetUniformLocation(_normalProgram.ID(), "transform");
		_textureLocationID_normal = glGetUniformLocation(_normalProgram.ID(), "tex");

		_projectionID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "projection");
		_transformID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "transform");
		_textureLocationID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "tex");

		_projectionID_outline = glGetUniformLocation(_outlineProgram.ID(), "projection");
		_transformID_outline = glGetUniformLocation(_outlineProgram.ID(), "transform");
		_init = true;
	}

	glGenBuffers(1, &_uvArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _extractor.GetUVMap().size(),
		     &(_extractor.GetUVMap()[0]),
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_normalArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _normalArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _extractor.GetNormals().size(),
		     &(_extractor.GetNormals()[0]),
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _extractor.GetVertices().size(),
		     &(_extractor.GetVertices()[0]),
		     GL_STATIC_DRAW);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     _textureParser.Width(),
		     _textureParser.Height(),
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     _textureParser.Data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	float aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_textureLocationID, 0);
}

Obj::~Obj(void)
{
	glDeleteBuffers(1, &_uvArrayID);
	glDeleteBuffers(1, &_normalArrayID);
	glDeleteBuffers(1, &_vertexArrayID);

	glDeleteTextures(1, &_textureID);
}

void	Obj::renderBackface(std::pair<glm::mat4, glm::mat4> perspective,
			    glm::mat4 transform,
			    glm::vec3 outlineColor,
			    glm::vec3 outlineSize)
{
}

void	Obj::Render(std::pair<glm::mat4, glm::mat4> perspective,
		    glm::mat4 transform,
		    glm::vec3 outlineColor,
		    float outlineSize,
		    bool cartoon)
{
	if (outlineColor.x == -1)
		renderBackface(perspective, transform, outlineColor, outlineSize);
	if (cartoon)
		_cartoonProgram.Use();
	else
		_normalProgram.Use();

	int size = Light::positions.size();

	if (size)
	{
		glUniform3fv(_lightPosID,
			     size,
			     reinterpret_cast<const GLfloat*>(&(Light::positions[0].x)));
		glUniform3fv(_lightColorID,
			size,
			reinterpret_cast<const GLfloat*>(&(Light::colors[0].x)));
		glUniform1fv(_lightFalloffID,
			size,
			&Light::falloffs[0]);
	}
	glUniform1i(_lightNumID, size);
}
