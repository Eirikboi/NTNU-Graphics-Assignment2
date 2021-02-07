#include <game_application.h>

void GameApplication::initializeInputCallbacks()
{
	//disabling the cursor in the window:
	glfwSetInputMode(this->gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//setting this to the userpointer:
	glfwSetWindowUserPointer(this->gameWindow, this);
	glfwSetCursorPosCallback(this->gameWindow, mouseCallback);
	glfwSetScrollCallback(this->gameWindow, scrollCallback);
	glfwSetKeyCallback(this->gameWindow, keyCallback);

}
#pragma region input_callbacks
void GameApplication::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	//setting global variables:
	//running processMouse():
	GameApplication* this_GLFWInput = (GameApplication*)glfwGetWindowUserPointer(window);
	this_GLFWInput->processMouse(xPos, yPos);
};
void GameApplication::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	//setting global variables:
	//globalGameInput.gameInputScrollPosition.x = x_offset;
	//globalGameInput.gameInputScrollPosition.y = y_offset;
	//running processScroll():
	GameApplication* this_GLFWInput = (GameApplication*)glfwGetWindowUserPointer(window);
	this_GLFWInput->processScroll(xOffset, yOffset);
};
void GameApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GameApplication* this_GLFWInput = (GameApplication*)glfwGetWindowUserPointer(window);
	this_GLFWInput->processKeyInput(key,scancode,action,mods);

};



void GameApplication::processMouse(double xPos, double yPos)
{
	//If this is the first time its used:
	if (globalGameInput.firstMouseUse)
	{
		globalGameInput.gameInputLastCursorPosition.x = xPos;
		globalGameInput.gameInputLastCursorPosition.y = yPos;
		globalGameInput.firstMouseUse = false;
	}
	globalGameInput.gameInputCursorOffset.x = xPos - globalGameInput.gameInputLastCursorPosition.x;
	//reversed since it Y goes from bottom to up:
	globalGameInput.gameInputCursorOffset.y = globalGameInput.gameInputLastCursorPosition.y - yPos;
	globalGameInput.gameInputLastCursorPosition.x = xPos;
	globalGameInput.gameInputLastCursorPosition.y = yPos;

//	std::cout << "mouse x: " << globalGameInput.gameInputCursorPosition.x << " and y: " << globalGameInput.gameInputCursorPosition.y << std::endl;

	this->gameObjects.updateInputCursorPosition();
};

void GameApplication::processScroll(double xOffset, double yOffset)
{
	globalGameInput.gameInputScrollPosition.x = xOffset;
	globalGameInput.gameInputScrollPosition.y = yOffset;
//	std::cout << "scroll x: " << globalGameInput.gameInputScrollPosition.x << " scroll y: " << globalGameInput.gameInputScrollPosition.y << std::endl;
	//requesting gameObjects to update their units dependent on scrollposition:
	this->gameObjects.updateInputScrollPosition();
};

void GameApplication::processKeyInput(int key, int scancode, int action, int mods)
{
	globalGameInput.Lastkey = key;
	globalGameInput.LastAction = action;
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(1);
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(2);
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(3);
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(4);
	}	
	
	if (key == GLFW_KEY_O&& action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(5);
	}
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(6);
	}
	if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(7);
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(8);
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		std::cout << "testing lighting:\n";
		this->gameObjects.addLight(9);
	}

	//this->gameObjects.updateInputKey(this->gameWindow,this->deltaTime, this->timeLastFrame);
};
#pragma endregion
