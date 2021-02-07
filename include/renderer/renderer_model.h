#ifndef	RENDERER_MODEL_H
#define RENDERER_MODEL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <renderer_vertex_data.h>
#include <renderer_shader.h>
#include <renderer_texture.h>
#include <vector>
#include <gl_error_handling.h>
#include<sstream>
#include <gfx.h>
#include <tiny_obj_loader.h>

//A renderable object inherits from the shader class and the texture class:
class Renderable
{
public:

	/////VARIABLES:
	////List of vertecies (position, color and texture):
	//std::vector<Vertex_Data> renderable_vertex_data;
	////List of indices:
	//std::vector<unsigned> renderable_vertex_indices;




	/////Number of indeces in renderable_vertex_indices. 
	//Saved and used for glDrawElements(GL_TRIANGLES, renderable.index_count, GL_UNSIGNED_INT, nullptr):
	GLuint indexCount{};
	///// HANDLERS/ IDS:
	GLuint vao{};
	GLuint vbo{};
	GLuint ebo{};


	/////FUNCTIONS:
	Renderable();
	~Renderable();
	//Initialise vbo and ebo(if used):
	bool initializeFromScratch(GLsizei stride, std::vector<VertexData> renderableVertexData, std::vector<unsigned>& indices);
	bool initializeWithObj(const std::string& fileName);
	void deleteRenderable();
	//Draw with indices:
	void drawElements(GLenum mode);
	//Draw without indices:
	void addToScene(GLenum mode, GLuint amountOfVertecies);
	//	static std::vector<Vertex_Data> load_object(const char* file_name);
	bool loadObject(const char* fileName);
	bool load(const std::string& filepathObject);

	std::vector<VertexData> vertices{}; // xxx 
	std::vector<GLuint> indices{};      // xxx

protected:	
	//A list of all textures initialized by this renderable
	//Each texture keeps track of their own ID and what state they're in (if they're animated):
private:
	/////LOCATIONS:
	GLuint vertexPositionLocation = 0;
	GLuint vertexColorLocation = 1;
	GLuint vertexTextureLocation = 2;
	GLuint vertexNormalLocation = 3;
//	GLuint vertex_color_location = 1;
	GLuint numberOfVertecies{};

	// xxx std::vector<VertexData> vertices{};
	// xxx std::vector<GLuint> indices{};

	int getVertexVectorPosition(VertexData* tempVertex);
	bool checkIfEqual(VertexData* tempVertex1, VertexData* tempVertex2);

};


#endif // !RENDERABLE_h
