#ifndef GAME_SQUARE_BOUNDS_H
#define GAME_SQUARE_BOUNDS_H


#include <vector>
#include <glm/glm.hpp>
#include <math.h>
#include <algorithm>
#include <game_intersectdata.h>
#include <glad/glad.h>


class Square {
public:
    // type of collision
    enum RIGITYPE { None, Dynamic, Kinematic, Player, Ray, RayCol };
    //RIGITYPE cur = None;

    Square(glm::vec3* minExtents, glm::vec3* maxExtents, glm::vec3* m_velocity, 
        glm::vec3* newVelocity, glm::vec3* m_pos, RIGITYPE* m_cur) :
        center(minExtents), 
        size(maxExtents), 
        vel(m_velocity),
        newVel(newVelocity),
        cur(m_cur),
        pos(m_pos) {}

    GLboolean IntersectSquare(Square other);

    glm::vec3 Max(glm::vec3 one, glm::vec3 two) const;
    //int Max(glm::vec3 one) const;
    IntersectData Max(glm::vec3 one);

    inline glm::vec3 GetMinExtents() const { return *center - *size + *vel; }
    inline glm::vec3 GetMaxExtents() const { return *center + *size + *vel; }

    inline glm::vec3 GetVel() const { return *vel; }
    // set newVel and velocity
    inline void SetVel(glm::vec3 val) { *newVel = *vel; *vel += val; }
    // for staring velocity movement without collision
    inline void initNewVel(glm::vec3 val) { *newVel = val; }

private:
    glm::vec3   *center,
                *size,
                *vel,
                * newVel,
                *pos;
    RIGITYPE*   cur;
};


#endif //!GAMEAABBS_H