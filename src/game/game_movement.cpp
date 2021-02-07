#include <game_movement.h>

Movement::Movement() {

}
void Movement::initialize(Camera *cam, GameObject *obj, GameObject* objGround, GameObject *world){
	this->camera = cam;
	this->camera = cam;
	this->obj = obj;
	this->objGround = objGround;
	this->world = world;
	this->floorPos = obj->transform.position.y - 4.5f;
}
//  check collision + update Gameobject/Camera position
void Movement::processInput(GLFWwindow* window, GLdouble deltaTime)
{
	// jumping
	jumping(window, deltaTime);
	// movement 
	movement(window, deltaTime);

	this->gameCameraTarget = GAME_WORLD_FORWARDS_VECTOR + this->obj->transform.position;
	// move camera. at head position
	camera->setCameraPositionVector(glm::vec3(obj->transform.position.x, obj->transform.position.y + 
		headPosForCamera, obj->transform.position.z + 0));
	// move ground checker.
	objGround->transform.position = glm::vec3(obj->transform.position.x, obj->transform.position.y  - 
		groundCheckerPos, obj->transform.position.z);
	
}
void Movement::update(GLFWwindow* window, GLdouble deltaTime)
{
	processInput(window, deltaTime);
	
}
//Input + Jumping
void Movement::jumping(GLFWwindow* window, GLdouble deltaTime)
{	
	// in air
	if (objGround->cur == Square::Ray) {
		force -= removeForce;
		jump = false;
		canJump = false;
	}
	// landing?
	if (canJump == false && objGround->cur == Square::RayCol)
	{
		objGround->cur = Square::Ray;
		canJump = true;
		jump = false;
		atPeak = false;
		force = 0;
		//obj->transform.m_velocity.y = 0;
		floorPos = obj->transform.position.y;
		removeForce = 0.02f;

	}
	// can jump and hit shift key for jumping
	if (glfwGetKey(window, globalGameInput.gameInputShift) == GLFW_PRESS && canJump == true) {
		canJump = false;
		jump = true;
	}
	// jumping
	if (jump == true && atPeak == false) {
		force += removeForce;
		force += addForce;
	}
	// at peak, stop adding jumpe force. and start add down force
	if (atPeak == false && obj->transform.position.y > floorPos + peak) {
		atPeak = true;
	}
	
}
//Input + movement  
void Movement::movement(GLFWwindow* window, GLdouble deltatime)
{
	float speed = moveSpeed * deltatime;
	// movement pos.x, pos.z
	obj->setVelocity(obj->transform.m_velocity + glm::vec3(0, force * deltatime, 0));
	// ground check velocity = player collider velocity
	objGround->setVelocity(obj->transform.m_velocity);

	if (glfwGetKey(window, globalGameInput.gameInputCtrl) == GLFW_PRESS)
	{
		// for testing. go -velocity.y.
		obj->setVelocity(obj->transform.m_velocity - glm::vec3(0, 0.1f, 0));

	}
	if (glfwGetKey(window, globalGameInput.gameInputMoveForwards) == GLFW_PRESS)
	{
		// moving forward
		obj->setVelocity(obj->transform.m_velocity
			+= glm::vec3(camera->getCameraDirectionVector().x, 0, camera->getCameraDirectionVector().z) * speed);

	}
	if (glfwGetKey(window, globalGameInput.gameInputMoveBack) == GLFW_PRESS)
	{

		obj->setVelocity(obj->transform.m_velocity
			-= glm::vec3(camera->getCameraDirectionVector().x, 0, camera->getCameraDirectionVector().z) * speed);

	}
	if (glfwGetKey(window, globalGameInput.gameInputMoveLeft) == GLFW_PRESS)
	{

		obj->setVelocity(obj->transform.m_velocity
			-= glm::normalize(glm::cross(this->camera->getCameraDirectionVector(), this->camera->getCameraUpVector())) * speed);

	}
	if (glfwGetKey(window, globalGameInput.gameInputMoveRight) == GLFW_PRESS)
	{

		obj->setVelocity(obj->transform.m_velocity
			+= glm::normalize(glm::cross(this->camera->getCameraDirectionVector(), this->camera->getCameraUpVector())) * speed);

	}

}