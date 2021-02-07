#ifndef GAME_INTERSECTDATA_H
#define GAME_INTERSECTDATA_H

#include <glm/glm.hpp>

class IntersectData
{
public:

	inline IntersectData() : m_doesIntersect(false), m_distance(0.f, 0.f, 0.f) {}
	inline IntersectData(const bool doesIntersect, const glm::vec3 distance) : 
		m_doesIntersect(doesIntersect), 
		m_distance(distance)	{}

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline glm::vec3 GetDistance()     const { return m_distance; }
private:
	// return bool and distance vec3
	const bool m_doesIntersect;
	const glm::vec3 m_distance;

};
#endif //!GAMEINTERSECTDATA_H