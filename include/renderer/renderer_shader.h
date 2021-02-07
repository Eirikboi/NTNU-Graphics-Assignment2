#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H
#include <resource_manager.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stb_image.h>
#include <iostream>
#include <global_renderer_shader_locations.h>
#include <renderer_light.h>

class Shader : public ResourceManager
{
public:
	Shader();
	~Shader();
	GLuint getShaderProgram() {
		return this->programID;
	}
	//compile_shader_from_filepath() reads to a string from file and compile that shader.
	//if succeeded it will return an ID for that shader.
	//type can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER:	
	GLuint compileShaderFromFilepath(const char* filepath, /*std::vector<std::string> locations,*/ GLenum type);
	//create_program links and creates a program of all the available shaders from the compiled_shader_ID_list:
	GLuint createProgram();

	//use_my_program, makes the current shader relevant:
	Shader& bindShaderProgram();
	//clear_compiled_shaders, deletes all the compiled shaders and clears the compiled_shader_ID_list:
	void clearCompiledShaders();

	void Shader::deleteShaderProgram();
	//get the this shader:
#pragma region setUniformValues

	// Utility functions copied from: https://learnopengl.com/code_viewer.php?code=in-practice/breakout/shader.h:
	void    setFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
	void    setInt(const GLchar* name, GLint value, GLboolean useShader = false);
	void    setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
	void    setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
	void    setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
	void    setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);
	//setting with a predefined location:
	void    setFloat(const unsigned location, GLfloat value, GLboolean useShader = false);
	void    setInt(const unsigned location, GLint value, GLboolean useShader = false);
	void    setVector2f(const unsigned location, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    setVector2f(const unsigned location, const glm::vec2& value, GLboolean useShader = false);
	void    setVector3f(const unsigned location, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    setVector3f(const unsigned location, const glm::vec3& value, GLboolean useShader = false);
	void    setVector4f(const unsigned location, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    setVector4f(const unsigned location, const glm::vec4& value, GLboolean useShader = false);
	void    setMatrix4(const unsigned location, const glm::mat4& matrix, GLboolean useShader = false);
	void    setMatrix3(const unsigned location, const glm::mat3& matrix, GLboolean useShader = false);

#pragma endregion

	/*Light is a pointer because shaders will share a light class, but that 
	might not always be the case so Light can't be static/singleton. What I'm trying
	to say is that a scene will share the same light class, but if I were to create several scenes
	these light classes needs to be seperate. Therefore they can't be singleton nor static
	they have to be normal objects, but referenced to so they can be shared between different 
	shaders in the SAME scene.*/
	void assignLight(Light* light) { 
		this->shaderLight = light; 
		this->shaderLight->initializeGameObject(this->programID);
		this->shaderLight->initializePointLight();
	};
	Light *shaderLight;// = Light::GetInstance();
private:
	//return_shader_compile_status checks the compilation status and prints an error if it fails:
	bool returnShaderCompileStatus(GLuint& shaderID);
	//return_program_link_status checks the linking status and prints an error if it fails:
	bool returnProgramLinkStatus(GLuint& programID);
	std::vector<std::string> locations{};

	//compile_shader compiles a shader and returns 
	//type can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER:
	GLuint compileShader(const char* source, GLenum type);

	//DONT USE DELETE AT SOME POINT:
	//GLuint make_shader(std::string vertexFilename, std::string fragmentFilename);

	//compiled_shader_ID_list used to keep track of all the compiled shaders
	//created by 	GLuint compile_shader_from_filepath(const char* filepath, GLenum type):
	std::vector<GLuint> compiledShaderListID{};
	//Id of the created by 	GLuint create_program(const std::vector<GLuint>& shaders):
	GLuint programID{}; 





	void initializeLight();
	int addLight(glm::vec3 lightPositon, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
		glm::vec3 colorSpecular, float constant, float linear, float quadratic);
	bool setLightPosition(int whichLight, glm::vec3& color);
	bool setColorAmbient(int whichLight, glm::vec3& color);
	bool setColorDiffuse(int whichLight, glm::vec3& color);
	bool setColorSpecular(int whichLight, glm::vec3& color);

};


#endif // !SHADER_H
