#ifndef GAME_RIGIDBODY_H
#define GAME_RIGIDBODY_H

#include <GLM/vec3.hpp>
#include <glad/glad.h>
#include <game_object.h>


class Rigidbody
{
private:
	
	GLboolean gravity = false;
	glm::vec3 force = glm::vec3(0,0,0);   
	GLfloat mass = 1;
	GameObject *obj;


public:

	

	//Rigidbody();
	void initialize(GameObject *obj,  GLboolean gravity, glm::vec3 force, GLfloat mass) {
		this->obj = obj;
		this->gravity = gravity;
		this->force = force;
		this->mass = mass;
	}
	void update(GLdouble deltatime) {
		gravityForce(deltatime);

	}
	// add gravity
	void gravityForce(GLfloat deltatime) {
		if (gravity) { obj->setVelocity(obj->transform.m_velocity + force * mass * deltatime); }
	}

};
#endif //!GAMERIGIDBODY_H
