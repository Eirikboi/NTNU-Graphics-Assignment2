#include <renderer_shader.h>

void Shader::initializeLight()
{
	//Pointlight Lightsources 
	this->shaderLight.initializeGameObject(this->programID);
}

int Shader::addLight(glm::vec3 lightPositon, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
	glm::vec3 colorSpecular, float constant, float linear, float quadratic)
{
	//if (this->lightUsed >= TOTAL_LIGHT_SOURCES)
	//{
	//	std::cout << "Shader::addLight() failed Can't add more point lighrtsources\n";
	//	return -1;
	//}
	//this->lightSources.push_back(PointLightSources);
	////Remember it's position:
	//this->lightSources[this->lightUsed++].setArrayLocation(lightUsed);
	//this->setInt(LIGHT_TOTAL_USED_LOCATION, this->lightUsed);
	//this->lightSources[lightUsed].lightposition = lightPositon;
	//this->setLightPosition(lightUsed, lightPositon)
	//	this->lightSources[lightUsed].colorAmbient = colorAmbient;
	//this->setColorAmbient(lightUsed, colorAmbient);
	//this->lightSources[lightUsed].colorDiffuse = colorDiffuse;
	//this->setColorDiffuse(lightUsed, colorDiffuse);
	//this->lightSources[lightUsed].colorSpecular = colorSpecular;
	//this->setColorSpecular(lightUsed, colorSpecular);
	//this->lightSources[lightUsed].constant = constant;
	//this->lightSources[lightUsed].linear = linear;
	//this->lightSources[lightUsed].quadratic = quadratic;

	////Returning the position in the array:
	//return (lightUsed - 1);
}

bool Shader::setLightPosition(int whichLight, glm::vec3& lightPosition)
{
	if (whichLight >= this->lightUsed)
	{
		return false;
	}
	std::string s = "setPointLightPosition[" + this->shaderArrayLocation;
	s += "]";
	this->setVector3f(s.c_str(), lightPosition);
	return true;
}
bool Shader::setColorAmbient(int whichLight, glm::vec3& color)
{
	std::string s = "pointLightSources[" + this->shaderArrayLocation;
	s += "].colorAmbient";
	this->setVector3f(s.c_str(), color);
}
bool Shader::setColorDiffuse(int whichLight, glm::vec3& color)
{
	std::string s = "pointLightSources[" + this->shaderArrayLocation;
	s += "].colorDiffuse";
	this->setVector3f(s.c_str(), color);

}
bool Shader::setColorSpecular(int whichLight, glm::vec3& color)
{
	std::string s = "pointLightSources[" + this->shaderArrayLocation;
	s += "].colorSpecular";
	this->setVector3f(s.c_str(), color);

}
bool Shader::setAttenuation(int whichLight, float constant, float linear, float quadratic)
{
	std::string sConstant = "pointLightSources[" + this->shaderArrayLocation;
	sConstant += "].constant";
	std::string sLinear = "pointLightSources[" + this->shaderArrayLocation;
	sLinear += "].linear";
	std::string sQuadratic = "pointLightSources[" + this->shaderArrayLocation;
	sQuadratic += "].quadratic";
	this->setFloat(sConstant.c_str(), constant);
	this->setFloat(sLinear.c_str(), linear);
	this->setFloat(sQuadratic.c_str(), quadratic);
}