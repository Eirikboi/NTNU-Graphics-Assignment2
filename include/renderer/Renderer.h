#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <struct_transform.h>

#include <renderer_light_shadows.h>
//#include <renderer_shader.h>
#include <renderer_texture.h>
#include <renderer_model.h>
#include <vector>
#include <global_renderer_information.h>

class Renderer
{
public:
	Renderer(GLuint windowWidth, GLuint windowHeight);

	~Renderer();

	//draw() draws the given renderable, texture and shader:
	bool addToScene(int virtual_renderable_id, int virtual_texture_id, int virtual_shader_id,
		glm::vec3* position, glm::vec3* size, GLfloat* rotate, glm::vec3* rotation_axis,
		glm::vec3* color);
//	bool draw(MeshData mesh);
//	bool addMeshData(GLuint virtualRenderableID, GLuint virtualTextureID, GLuint virtualShaderID); // xxx
	//update() updates
	void settingModelMatrices(Transform tr);
	bool settingMatrices(GLuint virtualShaderID);
	////RENDERABLES:
	//Loads a model from file and creates a renderable if successful.
	void addRenderable(int* renderableHandle, const char* imageFilePath);
	////SHADERS:
	void addShader(int* shaderHandle, const char* vertexFilePath, const char* fragmentFilePath, bool useLight = true);

	////TEXTURES:
	//add_texrure() adds a texture
	//to the textures and remembers it in the textures list:
	void addTexture(int* textureHandle, const std::string& imageFilePath/*, GLuint virtualShaderID*/, GLenum wrappingParam,
		GLenum minificationFilter, GLenum magnificationFilter);
	//add_texture_array() adds a texture_array
	//(like a sprite sheet) and remembers it in the texture list:
	void addTextureArray(int* textureHandle, const std::string& imageFilePath/*, GLuint virtualShaderID*/,
		GLuint starFrame, GLuint lastFrame, GLuint numberOfColumns, GLuint numberOfRows,
		GLenum wrappingParam, GLenum minificationFilter, GLenum magnificationFilter);
	//animate_texture_array() animates the texture if it's a texture_array. 
	//it will remember the amount of time to update to the next frame:
	bool animateTextureArray(GLuint virtualTextureID, GLuint frameRate, GLfloat deltaTime);
	bool setTextureArrayFrame(GLuint virtualTextureID, GLuint frame);

	//Sets the projection of the matrix to a orthologic projection:
	bool setOrthoProjection(GLuint windowWidth, GLuint windowHeight);
	//Sets the projection of the matrix:
	bool setPerspectiveProjection(GLuint windowWidth, GLuint windowHeight, GLfloat fieldOfViewInDegrees = 45.f);
	//Sets the camera to the set position, direction and rotation:
	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 upwards);
	void addLight(int* lightHandle, glm::vec3 lightPosition, glm::vec3 colorAmbient, glm::vec3 colorDiffuse,
		glm::vec3 colorSpecular, float constant, float linear, float quadratic);
	int removeLight(int &index);

	void acitaveDirLight(glm::vec3 &direction, glm::vec3 &ambientColor, glm::vec3 &diffuseColor, glm::vec3 &specularColor);
	void deacitaveDirLight();
	void editDirLight(glm::vec3* direction = nullptr, glm::vec3* ambientColor = nullptr, glm::vec3* diffuseColor = nullptr, glm::vec3* specularColor = nullptr);
	//drawScene draws the entire scene:
	void drawScene(int slett);
	void defineWindowDimentions(GLuint width, GLuint height);
private:
	Renderer() {};

	GlobalRenderInformation& renderInformation = GlobalRenderInformation::GetInstance();

	//update() updates
	bool settingModelAndNormalMatrices(int* virtualShaderID,
		glm::vec3* position, glm::vec3* size, GLfloat* rotate, glm::vec3* rotation_axis,
		glm::vec3* color);
	void settingViewAndProjectionMatrices(int* virtualShaderID) {

		this->shaders[*virtualShaderID].bindShaderProgram();
		this->shaders[*virtualShaderID].setMatrix4(MATRIX_PROJECTION_LOCATION, this->projection, true);
		this->shaders[*virtualShaderID].setMatrix4(MATRIX_VIEW_LOCATION, this->view, true);
	};
	//SceneInformation used to render the scene. This is done so we can render shadows without having to depend on the user of this renderer to 
	//render the shadowmap (or othber framebuffers) before the actual scene.
	struct SceneInformation
	{
		int *virtualRenderableID = nullptr;
		int *virtualTextureID	= nullptr;
		int *virtualShaderID		= nullptr;
		glm::vec3	*position		= nullptr;
		glm::vec3	*size			= nullptr;
		GLfloat		*rotate			= nullptr;
		glm::vec3	*rotation_axis	= nullptr;
		glm::vec3	*color			= nullptr;
		SceneInformation(
		int* virtualRenderableID, int* virtualTextureID, int* virtualShaderID, glm::vec3* position, 
		glm::vec3* size, GLfloat* rotate, glm::vec3* rotation_axis, glm::vec3* color
		)
		{
			this->virtualRenderableID	= virtualRenderableID;
			this->virtualTextureID = virtualTextureID;
			this->virtualShaderID = virtualShaderID;
			this->position = position;
			this->size = size;
			this->rotate = rotate;
			this->rotation_axis = rotation_axis;
			this->color = color;
		};
	};
	//Handles:	
	std::vector <int*> renderableHandles{};
	std::vector <int*> shaderHandles{};
	std::vector <int*> textureHandles{};

	std::vector<SceneInformation> scene{};
	Light light;
	Shadow shadow = Shadow(&light);
	glm::mat4 projection;

	//Renderables:
	std::vector<Renderable> renderables{};
	//Shaders:
	//they are individual shader programs that can be used for a specific renderable/texture:
	std::vector<Shader> shaders{};
	//Textures:
	std::vector<Texture> textures{};
	// vec meshes
	//std::vector<Mesh> meshes{};
	// func drawmesh(meshid) // bool draw(GLuint virtualRenderableID, GLuint virtualTextureID, GLuint virtualShaderID); xxx

	glm::mat4 model = glm::mat4(1);
	glm::mat4 view;
	glm::vec3 cameraPos{};
	glm::vec3 cameraTarget{};
	glm::vec3 cameraUp{};
};
#endif // !RENDERER_H
