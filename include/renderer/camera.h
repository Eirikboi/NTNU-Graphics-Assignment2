#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <global_game_variables.h>
#include <global_game_input.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
class Camera
{
public:
	Camera();
	~Camera();
	//void updateCamera();
	//set_camera() Sets the camera:
	void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 upwards = glm::vec3(0.f, 0.f, 1.f));
	//set_camera_speed(). shouldn't be less than 0:
	void setCameraSpeed(float speed);
	//update_camera() adds to the current camera position and rotation:

	
	//	void updateCamera(glm::vec3 posistion);
	
	
	void updateFieldOfView(/*double y_offset*/);
	void updateCursorPosition(/*double y_offset*/);


	//Get certain values:
	glm::vec3 getCameraPositionVector();
	void setCameraPositionVector(glm::vec3 newPosition);
	glm::vec3 getCameraTargetVector();
	glm::vec3 getCameraUpVector();
	glm::vec3 getCameraDirectionVector();
	glm::mat4 getViewMatrix();
	GLfloat getCameraFieldOfView();
	void processInput(GLFWwindow* window, GLdouble deltaTime);

private:
	GameInput& globalGameInput = GameInput::GetInstance();
	void getCursorPosition();

	//The core values to define the LookAt matrix:
	glm::vec3 gameCameraPosition = GAME_WORLD_STARTER_POSITION;
	glm::vec3 gameCameraTarget{};
	glm::vec3 gameCameraUp = GAME_WORLD_UP_VECTOR;
	glm::vec3 gameCameraDirection = GAME_WORLD_FORWARDS_VECTOR;
	glm::vec3 gameCameraRight{};
	//The speed of the camera movement:
	GLfloat gameCameraSpeed = 10.f;
	GLfloat gameCameraSensitivity = globalGameInput.MOUSE_SENSITIVITY;

	GLfloat fieldOfViewUpdate{}; //Used tp update the field of view in update()
	GLfloat fieldOfView = 45.f;
	GLfloat fieldOfViewMax = 90.f;
	GLfloat fieldOfViewMin = 20.f;
	glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), (float)GAME_WINDOW_WIDTH / (float)GAME_WINDOW_HEIGHT, 0.1f, 100.0f);

	//camera Yaw:
	GLfloat cameraYaw = -90.f;
	GLfloat cameraYawMax = -90.f;
	GLfloat cameraYawMin = -90.f;
	//camera Pitch:
	GLfloat cameraPitch = 0.f;
	GLfloat cameraPitchMax = 89.0f;
	GLfloat cameraPitchMin = -89.0f;
	//	GLfloat camera_roll = -90.f;


	//Processess and updates the camera:
	////Callback for mouse:
	//static void process_mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
	////Callback for scroll:
	//static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

		// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};




#endif // !CAMERA_H