#include <game_platform.h>

Platform::Platform()
{

}
// from obj postion + distance in direction of cur
// gameobj to move, movement speed, how far to go, direction
void Platform::initialize(GameObject *obj, GLfloat speed, GLfloat distance, DIR cur) {
	this->obj = obj;
	this->speed = speed;
	this->cur = cur;
	switch (cur)
	{
	case Platform::None:
		break;
	case Platform::Forward:
	{ this->distance = glm::vec3(0, 0, distance); target = obj->transform.position + this->distance; }
		break;
	case Platform::Backward:
	{ this->distance = glm::vec3(0, 0, distance); target = obj->transform.position - this->distance; }
		break;
	case Platform::Up:
	{ this->distance = glm::vec3(0, distance, 0); target = obj->transform.position + this->distance; }
	break;
	case Platform::Down:
	{ this->distance = glm::vec3(0, distance, 0); target = obj->transform.position - this->distance; }
	break;
	case Platform::Left:
	{ this->distance = glm::vec3(distance, 0, 0); target = obj->transform.position - this->distance; }
		break;
	case Platform::Right:
	{ this->distance = glm::vec3(distance, 0, 0); target = obj->transform.position + this->distance; }
		break;
	default:
		break;
	}
}
void Platform::update(GLdouble deltatime) {
	setDir(deltatime);
}
// sets det velocity all the time. add Kinematic = not affected by collision. than just set the vel once
void Platform::setDir(GLdouble deltatime) {
	
	switch (cur)
	{
	case Platform::None:
		break;
	case Platform::Forward:
	{ 
		this->obj->setInitVelocity(glm::vec3(0, 0, speed * deltatime)); 
		if (obj->transform.position.z > target.z)
		{
			this->target -=  distance;
			cur = Backward;
		}
	}
	break;
	case Platform::Backward:
	{ 
		this->obj->setInitVelocity(glm::vec3(0, 0, -speed * deltatime));
		if (obj->transform.position.z < target.z)
		{
			this->target += distance;
			cur = Forward;
		}
	}
	break;
	case Platform::Up:
	{ 
		this->obj->setInitVelocity(glm::vec3(0, speed * deltatime, 0));
		if (obj->transform.position.y > target.y)
		{
			this->target -= distance;
			cur = Down;
		}
	}
	break;
	case Platform::Down:
	{ 
		this->obj->setInitVelocity(glm::vec3(0, -speed * deltatime, 0));
		if (obj->transform.position.y < target.y)
		{
			this->target += distance;
			cur = Up;
		}
	}
	break;
	case Platform::Left:
	{ 
		this->obj->setInitVelocity(glm::vec3(-speed * deltatime, 0, 0));
		if (obj->transform.position.x < target.x)
		{
			this->target += distance;
			cur = Right;
		}
	}
	break;
	case Platform::Right:
	{ 
		this->obj->setInitVelocity(glm::vec3(speed * deltatime, 0, 0));
		if (obj->transform.position.x > target.x)
		{
			this->target -= distance;
			cur = Left;
			
		}
	}
	break;
	default:
		break;
	}
	//target = obj->transform.position + distance;
}