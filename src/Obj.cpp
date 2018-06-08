#include "Obj.hpp"

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

ShadingProgram Obj::_normalProgram(STANDARD_OBJ_VERTEX, "", STANDARD_OBJ_FRAG);
ShadingProgram Obj::_cartoonProgram(STANDARD_OBJ_VERTEX, "", CARTOON_OBJ_FRAG);
ShadingProgram Obj::_outlineProgram(OUTLINE_OBJ_VERTEX, "", OUTLINE_OBJ_FRAG);
bool	Obj::_init = false;

GLuint Obj::_projectionID_normal;
GLuint Obj::_transformID_normal;
GLuint Obj::_textureLocationID_normal;
GLuint Obj::_lightPosID_normal;
GLuint Obj::_lightColorID_normal;
GLuint Obj::_lightFalloffID_normal;
GLuint Obj::_lightNumID_normal;
GLuint Obj::_materialID_normal;

GLuint Obj::_projectionID_cartoon;
GLuint Obj::_transformID_cartoon;
GLuint Obj::_textureLocationID_cartoon;
GLuint Obj::_lightPosID_cartoon;
GLuint Obj::_lightColorID_cartoon;
GLuint Obj::_lightFalloffID_cartoon;
GLuint Obj::_lightNumID_cartoon;
GLuint Obj::_materialID_cartoon;

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
		_lightPosID_normal = glGetUniformLocation(_normalProgram.ID(), "lightPos");
		_lightColorID_normal = glGetUniformLocation(_normalProgram.ID(), "lightColor");
		_lightFalloffID_normal = glGetUniformLocation(_normalProgram.ID(), "lightFalloff");
		_lightNumID_normal = glGetUniformLocation(_normalProgram.ID(), "lightAmount");
		_materialID_normal = glGetUniformLocation(_normalProgram.ID(), "material");

		_projectionID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "projection");
		_transformID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "transform");
		_textureLocationID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "tex");
		_lightPosID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "lightPos");
		_lightColorID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "lightColor");
		_lightFalloffID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "lightFalloff");
		_lightNumID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "lightAmount");
		_materialID_cartoon = glGetUniformLocation(_cartoonProgram.ID(), "material");

		_projectionID_outline = glGetUniformLocation(_outlineProgram.ID(), "projection");
		_transformID_outline = glGetUniformLocation(_outlineProgram.ID(), "transform");
		_init = true;
	}
	
	float material[6] = {specular, diffuse, fog, fogcol.x, fogcol.y, fogcol.z};
	glUniform1fv(_materialID_normal, 6, material);
	glUniform1fv(_materialID_cartoon, 6, material);

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
			    glm::vec3 color,
			    float size)
{
	_outlineProgram.Use();
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glCullFace(GL_FRONT);
	
	glDrawArrays(GL_TRIANGLES, 0, _extractor.GetVertices().size() / 3);

	glDisableVertexAttribArray(0);
}

void	Obj::Render(std::pair<glm::mat4, glm::mat4> perspective,
		    glm::mat4 transform,
		    glm::vec3 outlineColor,
		    float outlineSize,
		    bool cartoon)
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	
	if (outlineColor.x != -1)
		renderBackface(perspective, transform, outlineColor, outlineSize);	

	glCullFace(GL_BACK);
	
	GLuint textureLocation[2] = {_textureLocationID_normal, _textureLocationID_cartoon};
	GLuint transformLocation[2] = {_transformID_normal, _transformID_cartoon};
	GLuint projectionLocation[2] = {_projectionID_normal, _projectionID_cartoon};
	GLuint lightPos[2] = {_lightPosID_normal, _lightPosID_cartoon};
	GLuint lightColor[2] = {_lightColorID_normal, _lightColorID_cartoon};
	GLuint lightFalloff[2] = {_lightFalloffID_normal, _lightFalloffID_cartoon};
	GLuint lightNum[2] = {_lightNumID_normal, _lightNumID_cartoon};
	
	if (cartoon)
		_cartoonProgram.Use();
	else
		_normalProgram.Use();

	glm::mat4 projection = perspective.second * perspective.first;
	glUniformMatrix4fv(projectionLocation[cartoon],
			   1,
			   GL_FALSE,
			   glm::value_ptr(projection));
	glUniformMatrix4fv(transformLocation[cartoon],
			   1,
			   GL_FALSE,
			   glm::value_ptr(transform));

	//lighting	
	int size = Light::positions.size();
	if (size)
	{
		glUniform3fv(lightPos[cartoon],
			     size,
			     reinterpret_cast<const GLfloat*>(&(Light::positions[0].x)));
		glUniform3fv(lightColor[cartoon],
			     size,
			     reinterpret_cast<const GLfloat*>(&(Light::colors[0].x)));
		glUniform1fv(lightFalloff[cartoon],
			size,
			&Light::falloffs[0]);
	}
	glUniform1i(lightNum[cartoon], size);

	glBindTexture(GL_TEXTURE_2D, _textureID);
	glActiveTexture(GL_TEXTURE0);

	glUniform1i(textureLocation[cartoon], 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _normalArrayID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, _extractor.GetVertices().size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisable(GL_CULL_FACE);
}
