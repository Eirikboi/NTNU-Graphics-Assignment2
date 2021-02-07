#ifndef RENDERER_SPRITE_H
#define RENDERER_SPRITE_H
//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer_model.h>
#include <vector>
#include <renderer_vertex_data.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <renderer_texture.h>

class Sprite : public Renderable
{
public:
	Sprite();
	~Sprite();
	void initializeSprite();
	//void draw_sprite(GLuint textureID, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, glm::mat4 projection);

private:
	
	//Sprite vertx:
	std::vector<VertexData> spriteVertexData;/* =
	{	// Position:		 //Color:			Texture coords:
		{{-0.5f,-0.5f}, {0.f,0.f}},	//Bottom Left 
		{ {0.5f,-0.5f}, {1.f,0.f}},	//Bottom Right
		{ {0.5f,0.5f},  {1.f,1.f}},		//Top right
		{ {-0.5f,0.5f}, {0.f,1.f}}		//Top left
	};*/
	//List of indices:
	std::vector<GLuint> spriteIndices =
	{
		0, 1, 2,
		2, 3, 0
	};

};
#endif //!SPRITE_H