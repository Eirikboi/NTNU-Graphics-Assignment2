#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H


#include <GLM/vec3.hpp>
#include <glad/glad.h>
#include <game_object.h>

class Platform
{
private:

	

public:
	enum DIR {None, Forward, Backward, Up, Down, Left, Right};
	DIR cur;
	// platform to move
	GameObject* obj;
	GLfloat speed;
	GLboolean changeDir = false;
	glm::vec3 distance = glm::vec3(0, 0, 0);
	glm::vec3 target;
	Platform();
	void initialize(GameObject *obj, GLfloat speed, GLfloat distance, DIR cur);
	void update(GLdouble deltatime);
	void setDir(GLdouble deltatime);

};
#endif //!GAMEPLATFORM_H
