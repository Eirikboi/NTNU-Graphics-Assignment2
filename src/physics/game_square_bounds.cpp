#include <game_Square_bounds.h>

//AABBS
GLboolean Square::IntersectSquare(Square other)
{
    //               center - size + vel   -(center - size + vel)
	glm::vec3 dis1 = other.GetMinExtents() - GetMaxExtents();
	glm::vec3 dis2 = GetMinExtents() - other.GetMaxExtents();
    //                    return biggest axis of both axises
    glm::vec3 distances = Max(dis1, dis2);
    // SetVel( empty vec3 with 1-3 axis with value.
    // with longest axis, nega or positiv
    //GLfloat maxDis = Max(distances);
    IntersectData xxx = Max(distances);
    // DYn
    if (xxx.GetDoesIntersect())
    {
        // Kinematic nothing happens. 
        if (*cur == Kinematic) { }
        else if (*cur == Dynamic )
        {
            // teleport back
            *pos += xxx.GetDistance();
            // set velocity
            initNewVel(-*vel);
        }
        // just collider
        else if (*cur == None)
        {
            SetVel(xxx.GetDistance());
        }
        else if (*cur == Player)
        {
            *pos += xxx.GetDistance();
        }
        // ray collider. do not check for player
        else if (*cur == Ray && *other.cur != Player)
        {
            *cur = RayCol;
        }
        
    }
    //return maxDis > 0 ? true : false;
    return xxx.GetDoesIntersect();
}

glm::vec3 Square::Max(glm::vec3 one, glm::vec3 two) const {
    glm::vec3 distances;
    for (unsigned int i = 0; i < 3; i++)
    {
        // one[axis] && two[axis] < 0.      and vel > 0         distances[axis] = one[axis]       
        if (one[i] < 0 && two[i] < 0 && GetVel()[i] > 0)        distances[i] = one[i];
        //              -//-                and vel < 0         distances[axis] = two[axis]  
        else if (one[i] < 0 && two[i] < 0 && GetVel()[i] < 0)   distances[i] = two[i];
        //                          distances[axis] = the biggest vec3[axis]
        else                        distances[i] = one[i] > two[i] ? one[i] : two[i];
    }
    return distances;
}


IntersectData Square::Max(glm::vec3 one) {
    GLfloat maxDis = one[0];
    int pos = 0;
    glm::vec3 distance{};
    // find axis with longest distance
    for (unsigned int i = 1; i < 3; i++)
    {
        if (maxDis < one[i]) { maxDis = one[i]; pos = i; }
    }
    if (maxDis < 0)
    {
        //               GetVel = current vel
        //longest dis =  ownVel[axis] if < 0, nega,    positiv
        distance[pos] = (GetVel()[pos] < 0) ? -maxDis : maxDis;
        // SetVel( empty vec3 with 1-3 axis with value.
        // with longest axis, nega or positiv
        //SetVel(distance);
    }
    return IntersectData(maxDis < 0, distance);
}

