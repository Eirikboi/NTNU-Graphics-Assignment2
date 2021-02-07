#include <renderer.h>

Renderer::Renderer(GLuint windowWidth, GLuint windowHeight)
{
	this->defineWindowDimentions(windowWidth, windowHeight);
	this->projection = glm::perspective(glm::radians(45.f), (float)this->renderInformation.RENDERER_WINDOW_WIDTH / (float)this->renderInformation.RENDERER_WINDOW_HEIGHT, 0.1f, 100.0f);
	this->view = glm::lookAt(this->renderInformation.RENDERER_WORLD_STARTER_POSITION, glm::vec3(0.f, 0.f, 0.f), this->renderInformation.RENDERER_WORLD_DIRECTION_UP);
}

Renderer::~Renderer()
{
	//deleting all the textures:
	for (auto i : textures)
	{
		i.deleteTexture();
	}
	for (auto i : shaders)
	{
		i.deleteShaderProgram();
	}
	for (auto i : renderables)
	{
		i.deleteRenderable();
	}
}








#pragma region add
//add_texture(..): adds a texture ti the renderer it will return a virtual id which the
//can be used to acces it. What we mean by virtual is that a it represents the position
//in the vector:
void Renderer::addTexture(int* textureHandle, const std::string& image_file_path/*, GLuint virtual_shader_id*/,
	GLenum wrapping_param = GL_REPEAT, GLenum minification_filter = GL_NEAREST,
	GLenum magnification_filter = GL_NEAREST)
{

	////Error handling:
	//if (virtual_shader_id >= shaders.size())
	//{
	//	std::cout << "Invalid virtual shader ID: " << virtual_shader_id << std::endl;
	//	return;
	//}
	Texture temp_texture;
	//If the loading texture fails:
	if (temp_texture.loadOpenglTexture(image_file_path, /*&this->shaders[virtual_shader_id], */wrapping_param, minification_filter, magnification_filter) == 0)
	{
		return;
	}

	this->textures.push_back(temp_texture);
	*textureHandle = this->textures.size() - 1;
	this->textureHandles.push_back(textureHandle);


	//	auto virtual_texture_location = (this->textures.size() - 1);
//	return virtual_texture_location;

	//NOTE!!! returning i instead of the actual Texture id so that the game object only keeps track of where it is in the vector of textures.
}

//add_texture_array(..): adds a texture array to the renderer it will return a virtual id which the
//can be used to acces it. What we mean by virtual is that a it represents the position
//in the vector:
void Renderer::addTextureArray(int* textureHandle, const std::string& image_file_path/*, GLuint virtual_shader_id*/,
	GLuint start_frame = 1, GLuint last_frame = 0, GLuint number_of_columns = 1, GLuint number_of_rows = 1,
	GLenum wrapping_param = GL_REPEAT, GLenum minification_filter = GL_NEAREST, GLenum magnification_filter = GL_NEAREST)
{
	////Error handling:
	//if (virtual_shader_id >= shaders.size())
	//{
	//	std::cout << "Invalid virtual shader ID: " << virtual_shader_id << std::endl;
	//	return;
	//}
	Texture temp_texture;
	//If loading texture fails:
	if (temp_texture.loadOpenGLTextureArray(image_file_path, /*&this->shaders[virtual_shader_id]*/ start_frame, last_frame,
		number_of_columns, number_of_rows, wrapping_param, minification_filter, magnification_filter) == 0)
	{
		return;
	}

	this->textures.push_back(temp_texture);
	*textureHandle = this->textures.size() - 1;
	this->textureHandles.push_back(textureHandle);

	//	auto virtual_texture_location = (textures.size() - 1);
		//NOTE!!! returning i instead of the actual Texture id so that the game object only keeps track of where it is in the vector of textures.
	//	return virtual_texture_location;
}
#pragma endregion
#pragma region animate
bool Renderer::animateTextureArray(GLuint virtual_texture_ID, GLuint frameRate, GLfloat deltaTime)
{
	if (this->textures.size() > virtual_texture_ID)
	{
		this->textures[virtual_texture_ID].animateTextureArray(frameRate, deltaTime);
		return true;
	}
	return false;
}

bool Renderer::setTextureArrayFrame(GLuint virtual_texture_ID, GLuint frame)
{
	if (virtual_texture_ID < this->textures.size())
	{
		return this->textures[virtual_texture_ID].setTextureArrayFrame(frame);
	}
	return false;
}
#pragma endregion


//Reading and creating an object from file:
void Renderer::addRenderable(int* renderableHandle, const char* ojb_file_path)
{
	//temporary renderable:
	Renderable temp_renderable;
	//initializes renderable:

	//If loading the model failed:
	if (!temp_renderable.initializeWithObj(ojb_file_path))
	{
		std::cout << "add_renderable()  failed to initialize\n";
		return;
	}

	//Handle managebent:
	this->renderables.push_back(temp_renderable);
	*renderableHandle = this->renderables.size() - 1;
	this->renderableHandles.push_back(renderableHandle);

	//return (renderables.size() - 1);

}
void Renderer::settingModelMatrices(Transform tr)
{
	model = glm::mat4(1);
	// First translate (transformations are: scale happens first, 
	//then rotation and then finall translation happens; reversed order):
	model = glm::translate(model, tr.position);
	// Move origin of rotation to center of quad:
//	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	//Then rotate:
	model = glm::rotate(model, glm::radians(tr.rotate), tr.rotationAxis);
	// Move origin back:
//	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
	// Last scale:
	model = glm::scale(model, tr.scale);
}

void Renderer::addShader(int* shaderHandle, const char* vertex_file_path, const char* fragment_file_path, bool useLight)
{
	Shader temp_shader;

	if (0 == temp_shader.compileShaderFromFilepath(vertex_file_path, GL_VERTEX_SHADER)) return;
	if (0 == temp_shader.compileShaderFromFilepath(fragment_file_path, GL_FRAGMENT_SHADER)) return;
	if (0 == temp_shader.createProgram()) return;
	//Assigning the shader to the light in this scene.
	if (useLight)
	{
		temp_shader.assignLight(&this->light);
	}
	shaders.push_back(temp_shader);
	*shaderHandle = this->shaders.size() - 1;
	this->shaderHandles.push_back(shaderHandle);

	//return (shaders.size() - 1);
}


void Renderer::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 upwards)
{
	this->cameraTarget = target;
	this->cameraPos = position;
	this->cameraUp = upwards;
	this->view = glm::lookAt(position, target, upwards);
}
//bool Renderer::draw(MeshData mesh)
//{
//	
//	if (mesh.virtualModelID >= this->renderables.size() || mesh.virtualTextureID >= this->textures.size() || mesh.virtualShaderID >= this->shaders.size())
//	{
//		std::cout << "Violating Renderer::draw(). invalid virtual_ID" << std::endl;
//		return false;
//	}
//	//Sets shader:
//	settingMatrices(mesh.virtualShaderID);
//	//Sets texture:
//	this->textures[mesh.virtualTextureID].bindTexture();
//	this->renderables[mesh.virtualModelID].drawElements(GL_TRIANGLES);
//
//
//}


//int Renderer::addRenderable(const std::string& ojb_file_path)



bool Renderer::setOrthoProjection(GLuint windowWidth, GLuint windowHeight)
{


	this->projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), 0.0f, static_cast<GLfloat>(windowWidth), -1.0f, 1.0f);

	return true;
}



bool Renderer::setPerspectiveProjection(GLuint windowWidth, GLuint windowHeight, GLfloat fov_in_degrees)
{
	this->projection = glm::perspective(glm::radians(fov_in_degrees), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	return true;
}


void Renderer::addLight(int* lightHandle, glm::vec3 lightPosition, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
	glm::vec3 colorSpecular, float constant, float linear, float quadratic)
//Reading and creating an object from file:
{
	this->light.addPointLight(lightHandle, lightPosition, colorAmbient, colorDiffuse,
		colorSpecular, constant, linear, quadratic);
}

int Renderer::removeLight(int& index)
{
	this->light.removePointLight(index);
	return 0;
}

void Renderer::acitaveDirLight(glm::vec3& direction, glm::vec3& ambientColor, glm::vec3& diffuseColor, glm::vec3& specularColor)
{
	this->light.createAndActivateDirectionalLight(direction, ambientColor, diffuseColor, specularColor);
	this->shadow.activateShadow();
	if (!this->shadow.initialized)
	{
		this->shadow.initializeGameObject();
	}
}
void Renderer::deacitaveDirLight()
{
	this->light.deactivateDirectionalLight();
	this->shadow.deactivateShadow();
}
void Renderer::editDirLight(glm::vec3* direction, glm::vec3* ambientColor, glm::vec3* diffuseColor, glm::vec3* specularColor)
{
	this->light.editDirectionalLight(direction, ambientColor, diffuseColor, specularColor);
}



bool Renderer::addToScene(int virtualRenderableHandle, int virtualTextureHandle, int virtualShaderHandle,
	glm::vec3* position, glm::vec3* size, GLfloat* rotate, glm::vec3* rotation_axis,
	glm::vec3* color)
{

	if (virtualRenderableHandle >= this->renderableHandles.size()
		|| virtualTextureHandle >= this->textureHandles.size()
		|| virtualShaderHandle >= this->shaderHandles.size())
	{
		std::cout << "Violating Renderer::addToScene(). invalid virtual_ID(s)" << std::endl;
		return false;
	}

	this->scene.push_back(
		SceneInformation(this->renderableHandles[virtualRenderableHandle], this->textureHandles[virtualTextureHandle], this->shaderHandles[virtualShaderHandle],
			position, size, rotate, rotation_axis, color));

}

unsigned int quadVAO = 0;
unsigned int quadVBO;


void Renderer::drawScene(int slett)
{
	float multiplier = 1.f;
	auto x = this->light.getLightDirection();
	x *= multiplier;
	glm::vec3 lightPos = this->cameraPos - x;
	auto dir = this->cameraTarget - this->cameraPos;
	//glm::vec3 lightPos = this->cameraPos - this->light.getLightDirection();
	//lightPos *= multiplier;
	auto cam = this->cameraPos;
//	cam *= multiplier;
	////Shadowmapping:
	//for (auto sceneObject : scene)
	//{
	//	this->settingModelAndNormalMatrices(sceneObject.virtualShaderID, sceneObject.position, sceneObject.size,
	//		sceneObject.rotate, sceneObject.rotation_axis, sceneObject.color);

	//	////Sets shader:
	//	this->shaders[*sceneObject.virtualShaderID].bindShaderProgram();
	//	////Sets texture:
	//	this->textures[*sceneObject.virtualTextureID].bindTexture();
	//	this->renderables[*sceneObject.virtualRenderableID].drawElements(GL_TRIANGLES);
	//}
	
	if (this->shadow.usingShadow)
	{

		glCullFace(GL_FRONT);
		glViewport(0, 0, this->renderInformation.SHADOW_WIDTH, this->renderInformation.SHADOW_HEIGHT);
		this->shadow.bindFramebruffer();
		this->shadow.clearFramebuffer();
		for (auto sceneObject : scene)
		{

			this->settingModelAndNormalMatrices(sceneObject.virtualShaderID, sceneObject.position, sceneObject.size,
				sceneObject.rotate, sceneObject.rotation_axis, sceneObject.color);

			this->shadow.configureShaderAndMatrices(this->cameraPos, dir, multiplier, this->model);
			this->renderables[*sceneObject.virtualRenderableID].drawElements(GL_TRIANGLES);
		}
		this->shadow.giveShadowMap();
		this->shadow.unbindFramebruffer();
		glViewport(0, 0, this->renderInformation.RENDERER_WINDOW_WIDTH, this->renderInformation.RENDERER_WINDOW_HEIGHT);
	
	glCullFace(GL_BACK); 


	}
	//Rendering the actual scene:
	for (auto sceneObject : scene)
	{

		this->settingModelAndNormalMatrices(sceneObject.virtualShaderID, sceneObject.position, sceneObject.size,
			sceneObject.rotate, sceneObject.rotation_axis, sceneObject.color);
		if (this->shadow.usingShadow)
		{
			this->shadow.sendViewSpaceMatrix(this->cameraPos, dir, multiplier);
		}

		



		//this->view = glm::lookAt(lightPos, cam, dir);
		//this->view = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0), glm::vec3(0.f, 1.f, 0.f));
		//this->view = glm::lookAt(glm::vec3(this->cameraPos - (this->light.getLightDirection() * 20.f)), this->cameraPos, glm::vec3(0.f, 1.f, 0.f));
		//this->projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.001f, 10000.5f);


		this->settingViewAndProjectionMatrices(sceneObject.virtualShaderID);
		
		////Sets shader:
		this->shaders[*sceneObject.virtualShaderID].bindShaderProgram();
		////Sets texture:
		this->textures[*sceneObject.virtualTextureID].bindTexture();
		this->renderables[*sceneObject.virtualRenderableID].drawElements(GL_TRIANGLES);
	}
	
	





	/*
	
	
	if (this->shadow.usingShadow)
	{

		if (this->shadow.usingShadow)
		{
			glViewport(0, 0, this->renderInformation.SHADOW_WIDTH, this->renderInformation.SHADOW_HEIGHT);
			this->shadow.bindFramebruffer();
			this->shadow.clearFramebuffer();
			for (auto sceneObject : scene)
			{

				this->settingModelAndNormalMatrices(sceneObject.virtualShaderID, sceneObject.position, sceneObject.size,
					sceneObject.rotate, sceneObject.rotation_axis, sceneObject.color);

				this->shadow.configureShaderAndMatrices(cam, dir, multiplier, this->model);
				this->renderables[*sceneObject.virtualRenderableID].drawElements(GL_TRIANGLES);
			}
			this->shadow.giveShadowMap();
			this->shadow.unbindFramebruffer();
			glViewport(0, 0, this->renderInformation.RENDERER_WINDOW_WIDTH, this->renderInformation.RENDERER_WINDOW_HEIGHT);

		}
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glCreateVertexArrays(1, &quadVAO);
			glCreateBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}

		this->shaders[slett].bindShaderProgram();
		//this->textures[*scene[0].virtualTextureID].slett();

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	*/
	scene.clear();
}


bool Renderer::settingModelAndNormalMatrices(int* virtualShaderId,
	glm::vec3* position, glm::vec3* size, GLfloat* rotate, glm::vec3* rotationAxis,
	glm::vec3* color)
{
#pragma region setting 
	if (virtualShaderId == nullptr)
	{
		return false;
	}
	if (*virtualShaderId >= this->shaders.size())
	{
		return false;
	}
	// First translate (transformations are: scale happens first, 
	//then rotation and then finall translation happens; reversed order):
	glm::mat4 model = glm::mat4(1);
	if (position)
	{
		model = glm::translate(model, *position);
	}
	else
	{
		model = glm::translate(model, glm::vec3(0));
	}
	// Move origin of rotation to center of quad:
	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	if (rotate && rotationAxis)
	{
		//Then rotate:
		model = glm::rotate(model, glm::radians(*rotate), *rotationAxis);
	}
	// Move origin back:
//	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
	// Last scale:
	if (size)
	{
		model = glm::scale(model, *size);
	}
	//calculating the normalMatrix:
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(this->view * model)));

	//setting the shader to 
	//this->shaders[virtual_shader_id].bind_shader_program();
	this->shaders[*virtualShaderId].bindShaderProgram();
	this->shaders[*virtualShaderId].setMatrix4(MATRIX_MODEL_LOCATION, model);
	this->shaders[*virtualShaderId].setMatrix3(MATRIX_NORMAL_LOCATION, normalMatrix);
	this->model = model;
	// Render textured quad
	if (color)
	{
		//	this->shaders[*virtual_shader_id].setVector3f("spriteColor", color);
	}
#pragma endregion
}

void Renderer::defineWindowDimentions(GLuint width, GLuint height)
{
	this->renderInformation.RENDERER_WINDOW_WIDTH = width;
	this->renderInformation.RENDERER_WINDOW_HEIGHT = height;
}