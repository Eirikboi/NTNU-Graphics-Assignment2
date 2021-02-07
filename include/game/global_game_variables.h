#ifndef GLOBAL_GAME_VARIABLES_H
#define GLOBAL_GAME_VARIABLES_H
// Pacman and ghost DIRECTION
// = NONE. can't have local enum with type NONE 
// and Global enum with type NONE // same vari name
enum DIRECTION { NONE, UP, DOWN, LEFT, RIGHT };
//Screen Width:
const int GAME_WINDOW_WIDTH = 1920;
//Screen Height:
const int GAME_WINDOW_HEIGHT = 1080;
//GAME_WORLD_UP_VECTOR is the universial up direction:
const glm::vec3 GAME_WORLD_UP_VECTOR = glm::vec3(0.f, 1.f, 0.f);
//GAME_WORLD_FORWARDS_VECTOR is the universial up direction:
const glm::vec3 GAME_WORLD_FORWARDS_VECTOR = glm::vec3(0.f, 0.f, 1.f);
//GAME_WORLD_LEFT_VECTOR is the universial up direction:
const glm::vec3 GAME_WORLD_LEFT_VECTOR = glm::vec3(1.f, 0.f, 0.f);
//GAME_WORLD_LEFT_VECTOR is the universial up direction:
const glm::vec3 GAME_WORLD_STARTER_POSITION = glm::vec3(0.f, 0.f, 10.f);

const int MAX_TOTAL_MESHES = 16;
const int MAX_TOTAL_VIRTUAL_TEXTURES = 32;
const int MAX_TOTAL_VIRTUAL_SHADERS = 32;
const int MAX_TOTAL_VIRTUAL_MODELS = 32;

#endif