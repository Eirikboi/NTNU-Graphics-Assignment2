#include <game_object.h>
#include <global_game_variables.h>

GLboolean GameObject::IntersectWithObject(GameObject* other)
{
    m_collider.IntersectSquare(other->m_collider);

    for (GameObject* child : other->children)
    {
        if (child != this) {
            // remove if
            IntersectWithObject(child) == true;
        }
        
    }
    return false;
}

// Update an object and all its children
void GameObject::update(GLdouble deltaTime) {


    transform.position += transform.m_velocity + parent->transform.m_velocity;
    transform.m_velocity = newVel;
	
}

void GameObject::setVelocity(glm::vec3 vel)
{
    this->transform.m_velocity = vel;
}
void GameObject::setInitVelocity(glm::vec3 vel)
{
    this->transform.m_velocity = vel;
    this->m_collider.initNewVel(vel);
}

