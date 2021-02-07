#ifndef RENDERER_LIGHT_SHADOWS_H
#define RENDERER_LIGHT_SHADOWS_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <global_renderer_shader_locations.h>
#include <global_renderer_information.h>
#include <algorithm>    // std::swap_ranges
#include <vector>       // std::vector
#include <renderer_shader.h>
#include <renderer_light.h>

class Shadow
{
public:
	Shadow(Light* light);
	~Shadow();
	void initializeGameObject();
	void configureShaderAndMatrices(glm::vec3 &Shadowposition, glm::vec3& cameraDirection, float &distanceMultiplier, glm::mat4 &model);
	void sendViewSpaceMatrix(glm::vec3 &Shadowposition, glm::vec3& position, float &distanceMultiplier);
	//	void renderModelToShadowmap(GLuint vao, GLuint ebo);
	void activateShadow();
	void giveShadowMap();
	void deactivateShadow();
	bool usingShadow = false;
	bool initialized = false;
	void bindFramebruffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	};
	void unbindFramebruffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};
	void clearFramebuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glClear(GL_DEPTH_BUFFER_BIT);
	}
private:
	Shadow() {};
	GlobalRenderInformation &renderInformation = GlobalRenderInformation::GetInstance();
	Shader	shadowShader;
	Light* light;
	//Frame buffer object to find whats visible to the lightsource and what's not.
	GLuint depthMapFBO{};
	GLuint depthMap{};
	glm::mat4 lightProjection  = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, 1.f, 20.5f);
	//glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.f, 10.5f);

//	glm::mat4 lightProjection  = glm::ortho(0.f, (float)RENDERER_WINDOW_WIDTH, 0.f, (float)RENDERER_WINDOW_HEIGHT, 1.f, 10.5f);
	glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	void renderScene();
};




#endif // !RENDERER_LIGHT_SHADOWS_H
