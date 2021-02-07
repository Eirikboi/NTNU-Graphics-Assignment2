#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/vec3.hpp>
#include <GLM/trigonometric.hpp>
#include <vector>
#include <struct_transform.h>
#include <game_mesh.h>
#include <vector>
#include <renderer_model.h>
#include <game_square_bounds.h>

//ALL GameObjects use the same Renderable because
//they are all (Wether they are the player, ghost, balls)
//rendered as a sprite with the same Vertex_structure and attributes.
//Therefore they will use the same VBO and VAO (and EBO):

static int iter = 0;

class GameObject
{

private:
	int *meshID;
	int objID;

public:

	Transform transform;

	GameObject* parent;
	std::vector<GameObject*> children;

	//std::vector<IntersectData> intersects;

	Square m_collider;
	glm::vec3 newVel;
	glm::vec3 beforeColVel = glm::vec3(0, 0, 0);
	GLboolean collided = false;
	glm::vec3 platformSize = glm::vec3(0,0,0);
	//Rigidbody rigi2;

	Square::RIGITYPE cur;

	//PhysicsObject physicsobject = PhysicsObject(&m_collider, transform.m_velocity);

	GameObject() : 
		parent(this), 
		objID(0), 
		transform{},
		newVel{},
		m_collider(&transform.position, &transform.scale, &transform.m_velocity, &newVel, &transform.position, &cur) { }

	GameObject(int* meshID, Transform tr, GameObject* par) :
		meshID(meshID),
		parent(par),
		transform(tr),
		newVel{},
		m_collider(&transform.position, &transform.scale, &transform.m_velocity, &newVel, &transform.position, &cur),
		objID(++iter) { par->children.push_back(this);
	}


	void setMeshID(int* id) { this->meshID = id; };
	
	GLboolean IntersectWithObject(GameObject* other);

	void update(GLdouble deltaTime);

	void setVelocity(glm::vec3 vel);

	void setRigidbody(Square::RIGITYPE cur) { this->cur = cur; };

	void setInitVelocity(glm::vec3 vel);

	inline float GetSumVelocity() { return transform.m_velocity.x + transform.m_velocity.y + transform.m_velocity.z; }

	inline int getMeshID() const { return *meshID; }
	// velocity != 0
	inline bool HasVelocity() const { return ((transform.m_velocity.x + transform.m_velocity.y + transform.m_velocity.z) != 0); }

	inline int getID() const { return objID; }

	/*
	void updateTransform(GLdouble deltaTime);
	Transform getTransform();
	void input();
	void render();
	void addChild(GameObject child);
	void addMesh(Mesh mesh);
	*/


	// consists of functions that recieve data from class
	
};
#endif //!GAMEOBJECT_H