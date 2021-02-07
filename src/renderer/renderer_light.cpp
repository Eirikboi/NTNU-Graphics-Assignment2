#include <renderer_light.h>




void Light::initializeGameObject(GLuint &shaderProgram)
{

	this->shaderProgram = shaderProgram;
	this->initializeShaderConnection();
}




	

void Light::initializePointLight()
{

}

void Light::initializeShaderConnection()
{

	if (!this->ShaderConnectionInitialized)
	{
		glCreateBuffers(1, &this->ubo);
		glNamedBufferStorage(this->ubo, sizeof(PointLight) * TOTAL_LIGHT_SOURCES, NULL, GL_DYNAMIC_STORAGE_BIT);
		glBindBufferBase(GL_UNIFORM_BUFFER, this->pointLightBlock.bindingLocation, this->ubo);

		////Setting up the uniform block connection:
		//this->uniformBuffer.createUniformBlockConnection(this->shaderProgram,
		//	this->pointLightBlock.blockName, this->pointLightBlock.blockSize, this->pointLightBlock.variableOffsets,
		//	this->pointLightBlock.variableArrayStride, this->pointLightBlock.variableMatrixStride, 
		//	this->pointLightBlock.variableLenght, this->pointLightBlock.bindingLocation);
	this->ShaderConnectionInitialized = true;
	}
}

void Light::addPointLight(int *lightHandle,glm::vec3 lightPosition, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
	glm::vec3 colorSpecular, float constant, float linear, float quadratic)
{
	if (*lightHandle > 0)
	{
		std::cout << "addPointLight() failed because *lightHandle is greater than 0, which means it's already assigned to a light source\n";
		return;
	}
	if (this->pointLights.size() >= TOTAL_LIGHT_SOURCES)
	{
		std::cout << "addPointLight() failed because number of point lights reached ( " << TOTAL_LIGHT_SOURCES << ")\n";
		return;
	}
	this->pointLights.push_back(
		PointLight{
			//floats:
				constant,
				linear,
				quadratic,
				0.f,
			//vec3:
				colorAmbient,
				0.f,
				colorDiffuse,
				0.f,
				colorSpecular,
				0.f
		});
	*lightHandle = pointLights.size();

	this->lightposition.push_back(lightPosition);

	this->lightHandles.push_back(lightHandle);
	//setting the variables:
	//this->uniformBuffer.setUniformBlockFloat(this->pointLightBlock.constant, constant);
	//this->uniformBuffer.setUniformBlockFloat(this->pointLightBlock.linear, linear);
	//this->uniformBuffer.setUniformBlockFloat(this->pointLightBlock.quadratic, quadratic);
	//this->uniformBuffer.setUniformBlockVec3(this->pointLightBlock.colorAmbient, colorAmbient);
	//this->uniformBuffer.setUniformBlockVec3(this->pointLightBlock.colorDiffuse, colorDiffuse);
	//this->uniformBuffer.setUniformBlockVec3(this->pointLightBlock.colorSpecular, colorSpecular);
	//sending data to shader uniform block:
	
	int i = this->pointLights.size() - 1;
	//this->uniformBuffer.sendBufferData();
	GLintptr offset = i * sizeof(PointLight);
	glNamedBufferSubData(this->ubo, offset, sizeof(PointLight), this->pointLights.data() + i);

	std::string s = "setPointLightPosition[" + std::to_string(i) + ']';

	glUniform1i(LIGHT_UNIFORM_TOTAL_USED_LOCATION, this->pointLights.size());
	glUniform3fv(glGetUniformLocation(this->shaderProgram, s.c_str()), 1, glm::value_ptr(lightPosition));
	glBindBufferBase(GL_UNIFORM_BUFFER, this->pointLightBlock.bindingLocation, this->ubo);
	return;
}
void Light::removePointLight(GLint handleIndex)
{

	int index = handleIndex - 1;
	int last = this->pointLights.size() - 1;
	if (index > last || index < 0)
	{

		std::cout << "removePointLight() failed because the index is invalid. Out of range\n";
		return;
	}

	//Making the handle light invalid:
	*this->lightHandles[index] = -1;
	//swapping vector objects to delete the last one:
	std::swap(this->pointLights[index], this->pointLights[last]);
	std::swap(this->lightposition[index], this->lightposition[last]);
	std::swap(this->lightHandles[index], this->lightHandles[last]);



	//removing the last element:
	this->pointLights.pop_back();
	this->lightposition.pop_back();
	this->lightHandles.pop_back();


	//Updating the data on the GPU:

	glUniform1i(LIGHT_UNIFORM_TOTAL_USED_LOCATION, this->pointLights.size());

	//if the index is the last one in the list i must be 
	if (index == lightHandles.size())
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, this->pointLightBlock.bindingLocation, this->ubo);
		return;
	}
	//Light handle index changes to the new position:
	*this->lightHandles[index] = (index + 1);


	if (this->lightposition.size() > 0)
	{
		std::string s = "setPointLightPosition[" + std::to_string(index) + ']';
		GLintptr offset = index * sizeof(PointLight);
		glNamedBufferSubData(this->ubo, offset, sizeof(PointLight), this->pointLights.data() + index);
		glUniform3fv(glGetUniformLocation(this->shaderProgram, s.c_str()), 1, glm::value_ptr(this->lightposition[index]));
	}
	glBindBufferBase(GL_UNIFORM_BUFFER, this->pointLightBlock.bindingLocation, this->ubo);

	return;
}

void Light::createAndActivateDirectionalLight(glm::vec3 &direction, glm::vec3 &ambientColor, glm::vec3 &diffuseColor, glm::vec3 &specularColor) 
{
	auto dir = glm::normalize(direction);
	glUniform3fv(LIGHT_DIRECTIONAL_DIRECTION_LOCATION, 1, glm::value_ptr(dir));
	glUniform3fv(LIGHT_DIRECTIONAL_COLOR_AMBIENT_LOCATION, 1, glm::value_ptr(ambientColor));
	glUniform3fv(LIGHT_DIRECTIONAL_COLOR_DIFFUSE_LOCATION, 1, glm::value_ptr(diffuseColor));
	glUniform3fv(LIGHT_DIRECTIONAL_COLOR_SPECULAR_LOCATION, 1, glm::value_ptr(specularColor));
	this->useDirLight = true;
	glUniform1i(LIGHT_DIRECTIONAL_USE_LOCATION, this->useDirLight);
	this->dirLight.lightdirection	= dir;
	this->dirLight.colorAmbient		= ambientColor;
	this->dirLight.colorDiffuse		= diffuseColor;
	this->dirLight.colorSpecular	= specularColor;
}
void Light::editDirectionalLight(glm::vec3* direction, glm::vec3* ambientColor, glm::vec3* diffuseColor, glm::vec3* specularColor)
{
	if (direction)
	{
		auto dir = glm::normalize(*direction);
		glUniform3fv(LIGHT_DIRECTIONAL_DIRECTION_LOCATION, 1, glm::value_ptr(dir));
		this->dirLight.lightdirection = dir;
	}
	if (ambientColor)
	{
		glUniform3fv(LIGHT_DIRECTIONAL_COLOR_AMBIENT_LOCATION, 1, glm::value_ptr(*ambientColor));
		this->dirLight.colorAmbient = *ambientColor;
	}
	if (diffuseColor)
	{
		glUniform3fv(LIGHT_DIRECTIONAL_COLOR_DIFFUSE_LOCATION, 1, glm::value_ptr(*diffuseColor));
		this->dirLight.colorDiffuse = *diffuseColor;
	}
	if (specularColor)
	{
		glUniform3fv(LIGHT_DIRECTIONAL_COLOR_SPECULAR_LOCATION, 1, glm::value_ptr(*specularColor));
		this->dirLight.colorSpecular = *specularColor;
	}

}
void Light::deactivateDirectionalLight()
{
	this->useDirLight = false;
	glUniform1i(LIGHT_DIRECTIONAL_USE_LOCATION, this->useDirLight);

}

void Light::renderShadow(GLuint vao)
{
	if (vao == 0)
	{
		std::cout << "Light::renderShadow() failed. vao is invalid\n";
		return;
	}
	this->renderShadow(vao);
}