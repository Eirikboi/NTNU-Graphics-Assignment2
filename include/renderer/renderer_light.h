#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <global_renderer_shader_locations.h>
#include <algorithm>    // std::swap_ranges
#include <vector>       // std::vector

/*
Light:
	- Not a singleton because even if several shaders will be using the same light source
	we might want to implement several scenes which would need to have several lighting classes.
*/

class Light
{
public:
	
	//static Light& GetInstance()
	//{
	//	static Light instance;
	//	return instance;
	//}
	Light() {};
	~Light() {};
	//initializeObject() sets up the lighting functionality in the shader:
	void initializeGameObject(GLuint& shaderProgram);
	void initializePointLight();
	//used to change the light. NOTE! values CAN be NULL!!! If not specified on first use it will be an ugly white light in direction
	//straight down:
	void createAndActivateDirectionalLight(glm::vec3 &direction, glm::vec3 &ambientColor, glm::vec3 &diffuseColor, glm::vec3 &specularColor);
	//used to change the light. NOTE! values CAN be NULL!!!:
	void editDirectionalLight(glm::vec3* direction = nullptr, glm::vec3* ambientColor = nullptr, glm::vec3* diffuseColor = nullptr, glm::vec3* specularColor = nullptr);
	void deactivateDirectionalLight();


	//call only once:
	void addPointLight(int* lightHandle, glm::vec3 lightPositon, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
		glm::vec3 colorSpecular, float constant, float linear, float quadratic);
	void removePointLight(GLint handleIndex);
	void renderShadow(GLuint vao);
	glm::vec3 getLightDirection() { return this->dirLight.lightdirection; };
private:
	bool useDirLight = false;
	bool directionalLightBeenUsed = false;

	GLuint ubo{};
	std::vector <int*> lightHandles{};
	//	static GameInput& instance;
	//Light() {};
	//Light(const Light& source) {};
	//Light(Light&& source) {};
	struct PointLight
	{
		float constant{};
		float linear{};
		float quadratic{};
		float _;
		glm::vec3 colorAmbient{};
		float __;
		glm::vec3 colorDiffuse{};
		float ___;
		glm::vec3 colorSpecular{};
		float ____;

	};
	//Not in the block, but used:
	std::vector<glm::vec3> lightposition{};

	struct DirectionalLight {
		glm::vec3 lightdirection{};
		glm::vec3 colorAmbient{};
		glm::vec3 colorDiffuse{};
		glm::vec3 colorSpecular{};
	};
	DirectionalLight dirLight{};
#pragma region PointLightConnection
	struct PointLightConnection {			//Block connection:
		const GLuint bindingLocation = 0;								//Binding
		//const char* blockName	= "PointLightBlock";						//BlockName
		//int blockSize						= 64;
		//std::vector <GLint>	variableOffsets = { 0,4,8,16,32,48 };		//Offset
		//std::vector <GLint>	variableArrayStride = { 0,0,0,0,0,0 };		//ArrayStride
		//std::vector <GLint>	variableMatrixStride = { 0,0,0,0,0,0 };		//MatrixStride
		//std::vector <GLint>	variableLenght = { 0,0,0,0,0,0 };			//ArrayLenght
		const enum blokVariableIndex { constant = 0, linear = 1, quadratic = 2,
			colorAmbient = 3, colorDiffuse = 4, colorSpecular = 5 };	//the index of each variable
		const int numberOfVariables = 3;

		static PointLightConnection& GetInstance()
		{
			static PointLightConnection instance;
			return instance;
		}

	private:
		//	static GameInput& instance;
		PointLightConnection() {};
		PointLightConnection(const PointLightConnection& source) {};
		PointLightConnection(PointLightConnection&& source) {};
	};
#pragma endregion

	GLuint shaderProgram;
	bool ShaderConnectionInitialized = false;

	//Point light:
	std::vector<PointLight> pointLights{};	//Light sources.



	int numberOfUsedLightSources{};					//number of used light sources.
	PointLightConnection& pointLightBlock = PointLightConnection::GetInstance();	//Information about uniform block in the shaders.
//	UniformBuffer uniformBuffer;
	void initializeShaderConnection();
	//connection to the shader.

	//The shaderprogram lightsource is assigned to:
//	Shader *shader = nullptr;		//What shader this light is assigned to.
};



#endif // !RENDERER_LIGHT_H
