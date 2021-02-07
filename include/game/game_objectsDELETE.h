#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer.h>
#include <renderer_sprite.h>
#include <renderer_vertex_data.h>
#include <camera.h>



//#include <Globalmap.h>

//ALL GameObjects use the same Renderable because
//they are all (Wether they are the player, ghost, balls)
//rendered as a sprite with the same Vertex_structure and attributes.
//Therefore they will use the same VBO and VAO (and EBO):
class GameObjects
{
public:

	GameObjects();
	~GameObjects();
	void initializeEverything();
	void drawGameObjects();
	void update(GLFWwindow* gameWindow, GLdouble deltaTime, GLdouble time);
	//updateInput...() updates input dependent units:
	void updateInputScrollPosition();
	void updateInputCursorPosition();
	void updateInputKey(GLFWwindow* gameWindow, GLdouble& deltaTime, GLdouble& time);
	void addLight(int x);
protected:

private:
	//Loads the textures:
	void loadTextures();
	glm::vec2 size = { 0.f, 0.f };
	GLuint width{}, height{};
	Renderer gameRenderer = Renderer(GAME_WINDOW_WIDTH,GAME_WINDOW_HEIGHT);
	Camera gameCamera;
};
#endif //!GAMEOBJECTS_H
