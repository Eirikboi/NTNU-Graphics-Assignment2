#ifndef GLOBAL_GAME_INPUT_H
#define GLOBAL_GAME_INPUT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//GameInput: mapping og keybindings
//and last updated gameInputs from callbacks:
struct GameInput
{
private:
//	static GameInput& instance;
	GameInput(){}
	GameInput(const GameInput& source){}
	GameInput(GameInput&& source){}
public:
	static GameInput& GetInstance()
	{
		//if (instance == nullptr)
		//	instance = new GameInput();

		//return instance;
		static GameInput instance;
		return instance;
	}
	//GameInput(GameInput const&) = delete;
	//GameInput(GameInput&&) = delete;
	const GLfloat MOUSE_SENSITIVITY = 0.25f;
	bool firstMouseUse = true;
	////MOUSE POSITION:
	//Last cursor position since moved:
	glm::vec2 gameInputLastCursorPosition{};
	glm::vec2 gameInputCursorOffset{};
	glm::vec2 gameInputScrollPosition{};
	//keys:
	int Lastkey;
	//The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.The key will be GLFW_KEY_UNKNOWN:
	int LastAction;
	////MOVEMENT:
	GLint gameInputMoveForwards = GLFW_KEY_W;
	GLint gameInputMoveBack = GLFW_KEY_S;
	GLint gameInputMoveLeft = GLFW_KEY_A;
	GLint gameInputMoveRight = GLFW_KEY_D;
	GLint gameInputShift = GLFW_KEY_LEFT_SHIFT;
	GLint gameInputCtrl = GLFW_KEY_LEFT_CONTROL;
	////MENU:
	GLint gameInputQuit = GLFW_KEY_ESCAPE;

};
/*
globalGameInput:
	* This is a global set of keybindings and current cursor position.
	* To change keybindings you will have to change this 
*/
//GameInput* globalGameInput = GameInput::GetInstance();

#endif // !GLOBAL_GAME_INPUT_H

