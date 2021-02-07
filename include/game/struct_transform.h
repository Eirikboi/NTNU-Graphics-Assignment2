#ifndef STRUCT_TRANSFORM_H
#define STRUCT_TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Transform
{
public:
//	Transform (glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation, glm::vec3 _velocity) :
//		position(_pos), scale(_scale), rotation(_rotation), m_velocity(_velocity) {}
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotationAxis;
	float rotate;
	glm::vec3 color;

	// speed, direction
	glm::vec3 m_velocity;
	
};

/*

class TransformList
{
private:
	std::vector<Transform> tList;

public:

	TransformList()  {}
	~TransformList() {}

	void initiateList();
	void addToList(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, float rotx, glm::vec3 col);
	void UpdateVelocity();
	Transform GetTransform(std::string ID);
	Transform GetTransform(std::string ID, std::string parentID);
	int decypherID(std::string ID);








	/*
	void Rotate(glm::vec3 axis, float angle);
	void LookAt(glm::vec3 point, glm::vec3 up);
	glm::vec4 GetLookAtRotation(glm::vec3 point, glm::vec3 up); //Quaternion
	GLboolean HasChanged();
	void SetParent(Transform parent);
	glm::vec3 GetTransformedPos();
	glm::vec4 GetTransformedRot(); //Quaternion
	glm::vec3 GetPos();
	void SetPos(glm::vec3 pos);
	glm::vec4 GetRot(); //Quaternion
	void SetRot(glm::vec4 rotation);
	glm::vec3 GetScale();
	void SetScale(glm::vec3 scale);


protected:

private:

};

*/

#endif //!STRUCT_TRANSFORM_H