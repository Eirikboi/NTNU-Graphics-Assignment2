#ifndef RENDERER_VERTEXDATA_H
#define RENDERER_VERTEXDATA_H

#include <glm/glm.hpp>
//Vertex_Data used for sprites:
struct VertexData
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
struct VertexIndices
{
	GLint vertexPositionIndicies;
	GLint vertexTexcoordIndicies;
	GLint vertexNormalIndicies;
	//is_equal(...) compares if the given structure is the same as itself:
	bool isEqual(VertexIndices vertexIndices)
	{
		if (
			(this->vertexPositionIndicies == vertexIndices.vertexPositionIndicies) &&
			(this->vertexTexcoordIndicies == vertexIndices.vertexTexcoordIndicies) &&
			(this->vertexNormalIndicies == vertexIndices.vertexNormalIndicies))
			return true;
		return false;
	};
};


#endif // !VERTEXDATA_H