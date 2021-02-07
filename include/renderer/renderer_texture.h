#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H
#include <resource_manager.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stb_image.h>
#include <renderer_shader.h>
//Used for getting sampler consts for texture:
#include <global_renderer_shader_locations.h>
//Texture:
//Remembers and deals with everything texture related:
class Texture : public ResourceManager
{
public:
	Texture();
	~Texture();
	GLuint loadOpenglTexture(const std::string& imagefilepath/*, Shader* shaderReference*/,
		GLenum wrappingParam, GLenum minificationFilter, GLenum magnificationFilter);
	// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
	// Texture configuration:
					//GLuint Wrap_S; // Wrapping mode on S axis
					//GLuint Wrap_T; // Wrapping mode on T axis
					//GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
						//GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
	// Binds the texture as the current active GL_TEXTURE_2D texture object
	//GLuint load_opengl_texture_array(const std::string& imagefilepath,
	//    GLenum wrapping_param, GLenum mipmap_param, GLuint internalformat, GLuint format,
	//    GLuint number_of_frames, GLuint number_horisontal_images, GLuint number_vertical_images);



		/////////ANIMATED SPRITE SHEETS:
	GLuint loadOpenGLTextureArray(const std::string& imageFilepath/*, Shader* shaderReference*/,
		GLuint startFrame, GLuint lastFrame, GLuint numberOfColumns, GLuint numberOfRows,
		GLenum wrappingParam, GLenum minificationFilter, GLenum magnificationFilter);

	//animates the texture array:
	bool animateTextureArray(GLuint frameRate, GLfloat deltaTime);
	//sets the texture array frame to a specific 
	bool setTextureArrayFrame(GLuint frame);


	//Bind this texture:
	void bindTexture();
	void deleteTexture();

	void slett() {
		glBindTextureUnit(SHADOW_DIRECTIONAL_TEXTURE_SAMPLE_LOCATION, this->textureID);
	}
private:
	//////Functions:
	std::vector<uint8_t> cutOneFrame(unsigned char* image, GLuint start, GLuint end, GLuint jump, GLuint width);
	//Function goes through char array and cuts out each frame accourding to the parameters. It will fail if the 
	//Rows and columns don't divide image_width/height into whole numbers:
	std::vector<std::vector<uint8_t>> cutImageIntoVectorlist(unsigned char* image, GLuint imageWidth, GLuint imageHeight,
		GLuint numbRows, GLuint numbColumns);


	//////Variables:
	GLuint textureSamplerLocation{};
	GLuint textureSamplerLayerLocation{};
	//GLuint usedShaderProgram{};


	//GL_TEXTURE_2D or GL_TEXTURE_2D_ARRAY:
	GLenum savedTarget{};
	//How many frames the sprite animation has:
	GLsizei numberOfFrames{};
	//Which frame to show (-1 by default):
	GLint currentFrame = TEXTURE_SAMPLER_UNUSED_LAYER;

	GLfloat timeSinceLastAnimationFrame{};
	GLuint textureID{};
	//Texture image dimensions:
	GLint textureWidth{}, textureHeight{};
	GLuint imageFormat{}; // Format of loaded image

};

#endif // !TEXTURE_H
