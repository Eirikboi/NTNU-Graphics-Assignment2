#include <game_objects.h>


void GameObjects::updateInputScrollPosition()
{
//	std::cout << "\Scrolling\n";
	this->gameCamera.updateFieldOfView();
	this->gameRenderer.setPerspectiveProjection(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, gameCamera.getCameraFieldOfView());
}
void GameObjects::updateInputCursorPosition()
{
//	std::cout << "\Cursor\n";
	this->gameCamera.updateCursorPosition();
	gameRenderer.setCamera(this->gameCamera.getCameraPositionVector(),this->gameCamera.getCameraTargetVector(), this->gameCamera.getCameraUpVector());

}

void GameObjects::updateInputKey(GLFWwindow* gameWindow, GLdouble &deltaTime, GLdouble &time)
{
//	std::cout << "hei\n";
	this->gameCamera.processInput(gameWindow,deltaTime);
	gameRenderer.setCamera(this->gameCamera.getCameraPositionVector(), this->gameCamera.getCameraTargetVector(), this->gameCamera.getCameraUpVector());

}

int lightHandle1{};
int lightHandle2{};
int lightHandle3{};
int lightHandle4{};

void GameObjects::addLight(int x)
{

	switch (x)
	{
	case 1:
		this->gameRenderer.addLight(&lightHandle1, glm::vec3(0.f,3.f,0.f), glm::vec3(0.2f, 0.5f, 0.8f), glm::vec3(0.9f, 0.4f, 0.6f), glm::vec3(0.9f, 0.8f, 0.9f), 0.25, 0.5, 0.125);
		std::cout << "handle1: " << lightHandle1 << std::endl;
		break;
	case 2:
		this->gameRenderer.addLight(&lightHandle2, glm::vec3(0.f,0.f,1.f), glm::vec3(0.f, 0.9f, 0.8f), glm::vec3(0.f, 0.9f, 0.6f), glm::vec3(0.9f, 0.f, 0.f), 0.25, 0.5, 0.125);
		std::cout << "handle2: " << lightHandle2 << std::endl;
		break;
	case 3:
		this->gameRenderer.addLight(&lightHandle3, glm::vec3(5.f,1.f,0.f), glm::vec3(0.f, 0.f, 0.9f), glm::vec3(0.9f, 0.4f, 0.f), glm::vec3(0.9f, 0.f, 0.f), 0.25, 0.5, 0.125);
		std::cout << "handle3: " << lightHandle3 << std::endl;
		break;
	case 4:
		this->gameRenderer.addLight(&lightHandle4, glm::vec3(0.f,5.f,8.f), glm::vec3(0.9f, 0.f, 0.f), glm::vec3(0.f, 0.4f, 0.f), glm::vec3(0.f, 0.f, 0.9f), 0.25, 0.5, 0.125);
		std::cout << "handle4: " << lightHandle4 << std::endl;
		break;
	case 5:
		this->gameRenderer.removeLight(lightHandle1);
		break;
	case 6:
		this->gameRenderer.removeLight(lightHandle2);
		break;
	case 7:
		this->gameRenderer.removeLight(lightHandle3);
		break;
	case 8:
		this->gameRenderer.removeLight(lightHandle4);
		break;
	case 9:

		this->gameRenderer.acitaveDirLight(glm::vec3(0.3f, -0.9f, 0.f), glm::vec3(0.2, 0.3, 0.5), glm::vec3(0.9f, 0.9f, 0.5f), glm::vec3(0.9f, 0.1f, 0.6f));
		break;
	default:
		break;
	}

}