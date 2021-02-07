#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H
//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gfx.h>
//GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Input:
#include <global_game_input.h>
//Game:
#include <game_objects.h>
#include <game_user_interface.h>
#include <gl_error_handling.h>
//String:
#include <string>

class GameApplication
{
public:
	GameApplication();
	~GameApplication();
	//initializeGlfwGlWindow() initializes the
	//window and relevant information:
	void initializeGlfwGlWindow();
	//initializeInputCallbacks() initializes specific input callbacks
	//that will run whenever there is an input:
	void initializeInputCallbacks();
	/////////////GAME:
	void gameRunLoop();
	void render(GLdouble timeSinceLastFrame, GLdouble time);
private:
	GLFWwindow* gameWindow = nullptr;
	/////////////APPLICATION:
	/////////////GAME:
	GameObjects gameObjects = GameObjects();
	void gameUpdate();

	void gameReset();
	/////////////FRAMERATE VARIABLES:
	//Delta time between each frame:
	GLdouble deltaTime{};
	//Amount of time since last frame:
	GLdouble elapsed;
	//Amount of time since last frame:
	GLdouble previous = 0;
	// Wanted Framerate:
	GLdouble MS_PER_UPDATE = 0.008f;
	//Used to display the framerate in the console:
	GLdouble currentFPS{};

	//UI
	void ui();

	/////////////IMGUI
	void imguiUpdate();
	void imguiInitialize();
	void imguiStarterWindow();
	bool imguiShowMenu = true;
	bool gameIsPaused = true;

////input callbacks:
#pragma region Callbacks
	GameInput& globalGameInput = GameInput::GetInstance();
	//mouseCallback() sets global cursor position and runs processMouse():
	static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
	//scrollCallback() sets the global scroll back position and runs processScroll():
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	//processMouse() runs all the relevant functions that are dependent on
	//cursor position (like updating camera):
	void processMouse(double xPos, double yPos);
	//processScroll() runs all the relevant functions that are dependent on
	//scroll position:
	void processScroll(double xOffset, double yOffset);
	void processKeyInput(int key, int scancode, int action, int mods);
	void create_debug_callback();
#pragma endregion

};


#endif // !GAMEAPPLICATION_H
