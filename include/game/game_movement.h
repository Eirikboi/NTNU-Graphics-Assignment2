#ifndef GAME_MOVEMENT_H
#define GAME_MOVEMENT_H

#include <camera.h>
#include <game_object.h>
#include <global_game_variables.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Movement {
public:
    Movement();
    void initialize(Camera *cam, GameObject *obj, GameObject* objGround, GameObject *world);

    void processInput(GLFWwindow* window, GLdouble deltaTime);
    void update(GLFWwindow* window, GLdouble deltaTime);
    void jumping(GLFWwindow* window, GLdouble deltaTime);
    void movement(GLFWwindow* window, GLdouble deltatime);

private:
    Camera *camera;
    GameObject* obj;
    // ground checker
    GameObject* objGround;
    GameObject *world;
    // floor pos.y
    float floorPos;
    GLboolean canJump = false;
    GLboolean jump = false;
    GLboolean atPeak = true;
    GLboolean landed = false;
    float moveSpeed = 2.0f;
    float headPosForCamera = 3.0f;
    float groundCheckerPos = 0.1f;
    // peak of jump
    float peak = 1.f;
    // Gravity and jump force
    float force = 0;
    // Gravity and jump force
    glm::vec3 forceVec;
    // jump force
    float addForce = 1.6;
    float removeForce = 0.004f;
    GameInput& globalGameInput = GameInput::GetInstance();

    glm::vec3 gameCameraTarget{};
};

#endif //!GAMEMOVEMENT_H