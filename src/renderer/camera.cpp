#include <camera.h>


Camera::Camera()
{
}

Camera::~Camera()
{
}


//void Camera::updateCamera(glm::vec3 posistion)
//{
//
//	return;
//}

void Camera::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 upwards)
{
	this->gameCameraPosition = position;
	this->gameCameraDirection = target;
	this->gameCameraUp = upwards;
}

void Camera::setCameraSpeed(float speed)
{
	this->gameCameraSpeed = speed;
}

glm::vec3 Camera::getCameraPositionVector()
{
	return this->gameCameraPosition;
}
void Camera::setCameraPositionVector(glm::vec3 newPosition)
{
	this->gameCameraPosition = newPosition;
}
glm::vec3 Camera::getCameraDirectionVector()
{
	return this->gameCameraDirection;
}
glm::vec3 Camera::getCameraUpVector()
{
	return this->gameCameraUp;
}
glm::vec3 Camera::getCameraTargetVector()
{
	return this->gameCameraTarget;
}
GLfloat Camera::getCameraFieldOfView()
{
	return this->fieldOfView;
}

//Processess and updates the camera:
void Camera::processInput(GLFWwindow* window, GLdouble deltaTime)
{
	this->gameCameraTarget = this->gameCameraDirection + this->gameCameraPosition;
}


void Camera::getCursorPosition()
{

}
void Camera::updateFieldOfView(/*double y_offset*/)
{
	//Setting the field of view:
	if (this->fieldOfView >= this->fieldOfViewMin && this->fieldOfView <= this->fieldOfViewMax)
	{
		this->fieldOfView -= globalGameInput.gameInputScrollPosition.y;
	}
	//If the FOV has exceeded the lowest FOV:
	if (this->fieldOfView < this->fieldOfViewMin)
	{
		this->fieldOfView = this->fieldOfViewMin;
	}
	//If the FOV has exceeded the highest FOV:
	if (this->fieldOfView > this->fieldOfViewMax)
	{
		this->fieldOfView = this->fieldOfViewMax;
	}
	//std::cout << "camera FOV: " << this->fieldOfView << std::endl;
	//std::cout << "Camera y: " << globalGameInput.gameInputScrollPosition.y << std::endl;

};
void Camera::updateCursorPosition(/*double y_offset*/)
{
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	GLboolean constrainPitch = true;
	GLfloat xoffset = globalGameInput.gameInputCursorOffset.x;
	GLfloat yoffset = globalGameInput.gameInputCursorOffset.y;
	xoffset *= this->gameCameraSensitivity;
	yoffset *= this->gameCameraSensitivity;

	this->cameraYaw += xoffset;
	this->cameraPitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{

		if (this->cameraPitch > this->cameraPitchMax)
			this->cameraPitch = this->cameraPitchMax;
		if (this->cameraPitch < this->cameraPitchMin)
			this->cameraPitch = this->cameraPitchMin;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
	//std::cout << "Global x: " << globalGameInput.gameInputCursorOffset.x << " y: " << globalGameInput.gameInputCursorOffset.y << std::endl;
	//std::cout << "Camera x: " << xoffset << " y: " << yoffset << std::endl;

}



void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->cameraYaw)) * cos(glm::radians(this->cameraPitch));
	front.y = sin(glm::radians(this->cameraPitch));
	front.z = sin(glm::radians(this->cameraYaw)) * cos(glm::radians(this->cameraPitch));
	this->gameCameraDirection = glm::normalize(front);
	this->gameCameraTarget = this->gameCameraPosition + this->gameCameraDirection;
	// Also re-calculate the Right and Up vector
	this->gameCameraRight = glm::normalize(glm::cross(this->gameCameraDirection, GAME_WORLD_UP_VECTOR));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->gameCameraUp = glm::normalize(glm::cross(this->gameCameraRight, this->gameCameraDirection));

}
// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->gameCameraPosition, this->gameCameraTarget, this->gameCameraUp);
}