#include <renderer_light_shadows.h>

Shadow::Shadow(Light* light)
{
	this->light = light;
}

Shadow::~Shadow()
{
}

void Shadow::initializeGameObject()
{

	glCreateFramebuffers(1, &this->depthMapFBO);
	glCreateTextures(GL_TEXTURE_2D, 1, &this->depthMap);
	glBindTextureUnit(SHADOW_DIRECTIONAL_TEXTURE_SAMPLE_LOCATION, this->depthMapFBO);
//	glBindTexture(GL_TEXTURE_2D, this->depthMap);

	this->shadowShader.compileShaderFromFilepath("resources/shaders/shadow_depth_vertex.vert", GL_VERTEX_SHADER);
	this->shadowShader.compileShaderFromFilepath("resources/shaders/shadow_depth_fragment.frag", GL_FRAGMENT_SHADER);
	auto x = this->shadowShader.createProgram();
	if (x == 0)
	{
		std::cout << "Shadow::initialize() failed because shader wouldn't compile\n";
		return;
	}
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTextureStorage2D(this->depthMap, 1, GL_DEPTH_COMPONENT32, this->renderInformation.SHADOW_WIDTH, this->renderInformation.SHADOW_HEIGHT);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glNamedFramebufferTexture(this->depthMapFBO, GL_DEPTH_ATTACHMENT, depthMap, 0);
	//Tell Opengl not to render color:
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->initialized = true;
}


void Shadow::configureShaderAndMatrices(glm::vec3 &cameraPosition,glm::vec3 &cameraDirection, float &distanceMultiplier, glm::mat4& model)
{

		//glm::vec3 lightDir = this->light->getLightDirection();
		//	glm::mat4 lightView = glm::lookAt(position - (lightDir * distanceMultiplier), position, glm::vec3(0.f,1.f,0.f));

	
	//SLETT
//	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
//	this->lightView = glm::lookAt(lightPos, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
//	this->lightSpaceMatrix = this->lightProjection * this->lightView;

	
//	glm::vec3 lightPos = position - this->light->getLightDirection() * distanceMultiplier;


			
	//Clearing up the scene:
	glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);

	this->shadowShader.bindShaderProgram();
	this->sendViewSpaceMatrix(cameraPosition,cameraDirection, distanceMultiplier);
	//this->shadowShader.setMatrix4(SHADOW_DIRECTIONAL_LIGHT_SPACE_MATRIX, this->lightSpaceMatrix);
	this->shadowShader.setMatrix4(SHADOW_DIRECTIONAL_MODEL_MATRIX, model);
	
}
void Shadow::sendViewSpaceMatrix(glm::vec3 &position, glm::vec3& directionUp, float &distanceMultiplier)
{
	auto liDir = this->light->getLightDirection();
	liDir *= distanceMultiplier;
	glm::vec3 lightPos = position - liDir;

	//glm::vec3 lightPos = position - this->light->getLightDirection();
	//lightPos += distanceMultiplier;
	this->lightView = glm::lookAt(lightPos, position, directionUp);
	//this->projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.f, 1000.5f);
	this->lightSpaceMatrix = this->lightProjection * this->lightView;

	//this->lightView = glm::lookAt(lightPos, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
	//this->lightSpaceMatrix = this->lightProjection * this->lightView;
	this->shadowShader.setMatrix4(SHADOW_DIRECTIONAL_LIGHT_SPACE_MATRIX, this->lightSpaceMatrix);
}


void Shadow::renderScene()
{

}
void Shadow::activateShadow() {
	this->usingShadow = true; 
}

void Shadow::deactivateShadow() { 
	this->usingShadow = false;
}


void Shadow::giveShadowMap()
{

	glBindTextureUnit(SHADOW_DIRECTIONAL_TEXTURE_SAMPLE_LOCATION, this->depthMap);

}

	//void Shadow::renderModelToShadowmap(GLuint vao, GLuint ebo)
	//{
	//	configureShaderAndMatrices();
	//	renderScene();
	//	// 2. then render scene as normal with shadow mapping (using depth map)
	//	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	//ConfigureShaderAndMatrices();
	//	//glBindTexture(GL_TEXTURE_2D, depthMap);
	//	//RenderScene();
	//	//glBindVertexArray(vao);
	//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//	//glDrawElements(mode, indexCount, GL_UNSIGNED_INT, nullptr);
	//}