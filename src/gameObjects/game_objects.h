#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/trigonometric.hpp>
#include <renderer_model.h>
#include <renderer.h>
#include <renderer_sprite.h>
#include <renderer_vertex_data.h>
#include <camera.h>
#include <game_object.h>		// has vector

#include <game_movement.h>
#include <game_platform.h>
#include <game_rigidbody.h>
#include <game_mesh.h>		// xxx
//#include <game_physics_engine.h>


//ALL GameObjects use the same Renderable because
//they are all (Wether they are the player, ghost, balls)
//rendered as a sprite with the same Vertex_structure and attributes.
//Therefore they will use the same VBO and VAO (and EBO):
class GameObjects
{
private:

	/*
	NOTE!
	DUMMY data that is not supposed to be here if we were to continue this project.
	*/
	std::vector<std::vector<int>> DUMMYmeshesToAssignTexture;
	std::vector<std::vector<int>> DUMMYmeshesToAssignModels;
	std::vector<std::vector<int>> DUMMYmeshesToAssignShaders;
	std::vector<std::vector<int>> DUMMYgameObjectToAssignMeshes;
	std::vector<std::string> DUMMYtexturesFileNames;
	std::vector<std::string> DUMMYmodelFileNames;
	std::vector<std::string> DUMMYvertexShaderFileNames;
	std::vector<std::string> DUMMYfragmentShaderFileNames;
	int DUMMYamountOfMeshes;

	void initiateHardcodedDummyList();

	glm::vec2 size = { 0.f, 0.f };
	GLuint width{}, height{};
	Renderer gameRenderer = Renderer(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
	Camera gameCamera;
	Movement player;// = Movement();
	Platform platform;
	Platform platform2;
	Platform platform3;
	std::vector<Platform*> platforms;
	Rigidbody rigi;
	std::vector<Rigidbody*> rigis;

	


	//Transform transform;
	//TransformList transforms = TransformList();

	Mesh mesh = Mesh();

	std::vector<int> meshHandles = std::vector<int>(MAX_TOTAL_MESHES);

	//std::vector<Mesh> meshes;
	GameObject world = GameObject();					// Worldview
	GameObject* element;				// Individual element being created
	std::vector<GameObject*> objects;	// All elements created are being stored in an array
	//int iterator = -1;

	//PhysicsEngine physicsEngine = PhysicsEngine();
	void renderObjects(GameObject* obj, GLdouble time);

public:

	GameObjects() {}
	~GameObjects() {}
	void initializeEverything();
	void initializeGameObject(int* ID, Transform tr, GameObject* par);
	void initiateHardcodedMeshes();
	void update(GLFWwindow* gameWindow, GLdouble deltaTime, GLdouble time);
	void render(GLdouble timeSinceLastFrame, GLdouble time);
	//GLboolean CheckCollision(GameObject& one, GameObject& two); // xxx
	//void Collisions(); // xxx
	//updateInput...() updates input dependent units:
	void updateInputScrollPosition();
	void updateInputCursorPosition();
	void updateInputKey(GLFWwindow* gameWindow, GLdouble& deltaTime, GLdouble& time);
	Mesh setMesh(glm::vec3 pos, glm::vec3 size, glm::vec3 rot, GLfloat rotate, glm::vec3 col, int shad, int rend, int tex);

	void addLight(int x);
	void esben();
	void tobias();

};
#endif //!GAMEOBJECTS_H
