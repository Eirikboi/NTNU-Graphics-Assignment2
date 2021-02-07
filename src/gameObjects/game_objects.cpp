#include <game_objects.h>
#include <global_game_variables.h>




//Initialize() Initializes everything that needs to be initialized:
void GameObjects::initializeEverything()
{
	
    //Player [0]
	initializeGameObject(nullptr, Transform{ glm::vec3(4.0f, 3.0f, 10.f), glm::vec3(0.3f, 0.03f, 0.3f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);
	objects[0]->setRigidbody(Square::RIGITYPE::Player);
	// Player ground checker
	initializeGameObject(nullptr, Transform{ glm::vec3(4.0f, 3.f, 10.f), glm::vec3(0.1f, 0.01f, 0.1f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);
	objects[1]->setRigidbody(Square::RIGITYPE::Ray);

	initiateHardcodedMeshes();
    esben();
    //tobias();


    player.initialize(&gameCamera,
		*&objects[0],
		*&objects[1],
        &world
    );
    
}
void GameObjects::esben()
{
	////// initialize("#00#00", &world);
	initializeGameObject(nullptr, Transform{ glm::vec3(10, -6, -30.f), glm::vec3(4.0f, 3.0f, 4.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);
	// platform moving
	platform.initialize(*&objects[2], 1.9f, 10, Platform::Backward);
	platforms.push_back(&platform);
	
	initializeGameObject(nullptr, Transform{ glm::vec3(0, -6, -15.f), glm::vec3(4.0f, 3.0f, 4.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	platform2.initialize(*&objects[3], 1.9f, 10.f, Platform::Left);
	platforms.push_back(&platform2);

	initializeGameObject(nullptr, Transform{ glm::vec3(-9, -6, -30.f), glm::vec3(4.0f, 3.0f, 4.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);
	platform3.initialize(*&objects[4], 1.9f, 5.f, Platform::Up);
	platforms.push_back(&platform3);

	// when colliding do collision math. vel = -vel
	initializeGameObject(nullptr, Transform{ glm::vec3(7.0f, 5.9f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	objects[5]->setRigidbody(Square::Dynamic);
	objects[5]->setInitVelocity(glm::vec3(0.09f, -0.021f, -0.000f));

	// collider, stop from going in to walls
	initializeGameObject(nullptr, Transform{ glm::vec3(5.0f, 5.9f, -3.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	objects[6]->setRigidbody(Square::None);
	objects[6]->setInitVelocity(glm::vec3(0.09f, -0.021f, -0.000f));

	
	//initializeGameObject(nullptr, Transform{ glm::vec3(5.0f, 7.9f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	//objects[7]->setRigidbody(Square::None);
	//rigi.initialize(objects[7], true, glm::vec3(0.00f, -0.08f, 0.f), 1);
	//rigis.push_back(&rigi);
    
	// House
	initializeGameObject(nullptr, Transform{ glm::vec3(10.0f, -8.f, 1.8f), glm::vec3(10.0f, 4.0f, 10.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	initializeGameObject(nullptr, Transform{ glm::vec3(21.1f, 5.1f, 2.f), glm::vec3(1.0f, 10.0f, 10.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	initializeGameObject(nullptr, Transform{ glm::vec3(-1.1f, 5.1f, 2.f), glm::vec3(1.0f, 10.0f, 10.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
	initializeGameObject(nullptr, Transform{ glm::vec3(10.1f, 5.1f, 13.f), glm::vec3(9.0f, 10.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one

	for (auto i : objects)
	{
		i->setMeshID(&this->meshHandles[0]);
	}
    
}
void GameObjects::tobias()
{
    // gameobject
	// initialize("#00#00", &world);
    initializeGameObject(nullptr, Transform{ glm::vec3(-8.0f, 1.9f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
    //initialize(1, { Transform(glm::vec3(0.0f, 1.9f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f)) }, &world);     // Minecraft block one
    initializeGameObject(nullptr, Transform{ glm::vec3(-10.0f, 3.f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block two
    
    // Floor & walls
    initializeGameObject(nullptr, Transform{ glm::vec3(-11.0f, -6.f, 0.f), glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
    initializeGameObject(nullptr, Transform{ glm::vec3(-21.0f, 6.f, 0.f), glm::vec3(1.0f, 10.0f, 10.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);     // Minecraft block one
    
	
	initializeGameObject(nullptr, Transform{ glm::vec3(5.0f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);                       // Minecraft block one
	initializeGameObject(nullptr, Transform{ glm::vec3(2.0f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.f, 1.f, 0.f), 0, glm::vec3(1.f, 1.f, 1.f) }, &world);                       // Minecraft block two

	initiateHardcodedMeshes();

	objects[0]->setVelocity(glm::vec3(-0.01f, 0.005f, 0.00f));

}

void GameObjects::initializeGameObject(int *ID, Transform tr, GameObject* par)
{
	element = new GameObject(ID, tr, par);
	//element->transform = transforms.getTransform(element->getMeshID());
	objects.push_back(element);

	//physicsEngine.AddObject(element->physicsobject);
}
void GameObjects::initiateHardcodedDummyList()
{
	DUMMYamountOfMeshes = 3;
	//for each int vector it tells which meshes should be assinged this texture:
	//first textures shall be shader by mesh 0 and 1, 
	DUMMYtexturesFileNames = { "diamond.png", "axe_color.png" };
	DUMMYmodelFileNames = { "untitled.obj", "axe.obj" };
	DUMMYvertexShaderFileNames = { "sprite_vertex.vert" };
	DUMMYfragmentShaderFileNames = { "sprite_fragment.frag" };


	//while the third mesh will have the last texture alone:
	DUMMYmeshesToAssignTexture = { {0,1},{2} };
	//first model shall be shader by mesh 0 and 1, 
	//while the third mesh will have the last model alone:
	DUMMYmeshesToAssignModels = { {0,1},{2} };
	//all the meshes will be sharing the same shader program:
	DUMMYmeshesToAssignShaders = { {0,1,2} };
	DUMMYgameObjectToAssignMeshes = { {0,1}, {} , {} };
}
void GameObjects::initiateHardcodedMeshes()
{
	//	std::vector<int*> meshIDs{};


	std::cout << "hei1\n";
	this->initiateHardcodedDummyList();

	for (int h = 0; h < DUMMYamountOfMeshes; h++)
	{
		//		int meshID = -1;
		//		meshIDs.push_back()
//		this->meshHandles.push_back(0);
		mesh.addMesh(&this->meshHandles[h]);
		/*
		for (int i = 0; i < DUMMYgameObjectToAssignMeshes[h].size(); i++)
		{

			auto index = DUMMYgameObjectToAssignMeshes[h][i];
			objects[index]->setMeshID(&this->meshHandles.back());

		}
		*/
	}
	//Assigning meshes a model/renderables:
	for (int i = 0; i < DUMMYmeshesToAssignModels.size(); i++)
	{
		//Reserving a pointer in mesh to then be give to the renderer:
		auto ID = this->mesh.allocateModelID();
		//Loading model:
		gameRenderer.addRenderable(ID, ("resources/objects/" + DUMMYmodelFileNames[i]).c_str());
		//Looping through all the meshes which is assigned to this model:
		for (int j = 0; j < DUMMYmeshesToAssignModels[i].size(); j++)
		{
			//Assigns this meshes ID pointer to the ID recieved from the renderer:
			mesh.meshDatas[DUMMYmeshesToAssignModels[i][j]].virtualModelID = ID;
		}
	}
	//Assigning meshes a texture:
	for (int i = 0; i < DUMMYmeshesToAssignTexture.size(); i++)
	{
		//Reserving a pointer in mesh to then be give to the renderer:
		auto ID = this->mesh.allocateTextureID();
		//Loading model:
		gameRenderer.addTexture(ID, "resources/textures/" + DUMMYtexturesFileNames[i], GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		//Looping through all the meshes which is assigned to this model:
		for (int j = 0; j < DUMMYmeshesToAssignTexture[i].size(); j++)
		{
			//Assigns this meshes ID pointer to the ID recieved from the renderer:
			mesh.meshDatas[DUMMYmeshesToAssignTexture[i][j]].virtualTextureID = ID;
		}
	}
	//Assigning meshes a shader:
	for (int i = 0; i < DUMMYmeshesToAssignShaders.size(); i++)
	{
		//Reserving a pointer in mesh to then be give to the renderer:
		auto ID = this->mesh.allocateShaderID();
		//Loading model:
		gameRenderer.addShader(ID, ("resources/shaders/" + DUMMYvertexShaderFileNames[i]).c_str(), ("resources/shaders/" + DUMMYfragmentShaderFileNames[i]).c_str());
		//Looping through all the meshes which is assigned to this model:
		for (int j = 0; j < DUMMYmeshesToAssignShaders[i].size(); j++)
		{
			//Assigns this meshes ID pointer to the ID recieved from the renderer:
			mesh.meshDatas[DUMMYmeshesToAssignShaders[i][j]].virtualShaderID = ID;
		}
	}
	if (DUMMYamountOfMeshes > 0)
	{

		std::cout << "hei2\n"
			<< this->DUMMYmodelFileNames[0].c_str() << std::endl
			<< this->DUMMYtexturesFileNames[0].c_str() << std::endl;
	}

}

void GameObjects::update(GLFWwindow* gameWindow, GLdouble deltaTime, GLdouble time)
{

	this->gameCamera.processInput(gameWindow, deltaTime);
	this->gameRenderer.setCamera(this->gameCamera.getCameraPositionVector(), this->gameCamera.getCameraTargetVector(), this->gameCamera.getCameraUpVector());

	//for(GameObject* child : world.children) renderObjects(child, time);
//	renderObjects(objects[0], time);
    //Player
    player.update(gameWindow, deltaTime);
    for (Platform* child : platforms) child->update(deltaTime);
    for (Rigidbody* child : rigis) child->update(deltaTime);
    // obj.update and collision

	//physicsEngine.Simulate(deltaTime);
	//physicsEngine.HandleCollisions();

    //physicsEngine.Simulate(deltaTime);
    //physicsEngine.HandleCollisions();
    

}
void GameObjects::render(GLdouble timeSinceLastFrame, GLdouble time)
{
	for (GameObject* child : world.children) renderObjects(child, timeSinceLastFrame);
	//renderObjects(objects[0], time);




	///LA STÅ. Trenger noe for å vise ligting:
	auto	apos = glm::vec3(4.f, 0.5f, 0.f);
	auto	asize = glm::vec3(0.02f);
	auto	arotationaxis = glm::vec3(0.f, 0.f, 1.f);
	auto	acolor = glm::vec3(1.f);
	float	arotate = 20 * time;

	gameRenderer.addToScene(*this->mesh.meshDatas[2].virtualModelID, *this->mesh.meshDatas[2].virtualTextureID, *this->mesh.meshDatas[2].virtualShaderID, &apos, &asize, &arotate, &arotationaxis, &acolor);
	gameRenderer.drawScene(1);

}
void GameObjects::renderObjects(GameObject* obj, GLdouble time)
{
    if (obj->HasVelocity() || obj->cur == Square::Ray)
    {
        
        for (GameObject* child : world.children)
        {
            if (child != obj) obj->IntersectWithObject(child);
        }
    }

    obj->update(time);

    

    //objects[1]->update(time);
	auto meshToRender = mesh.getMesh(obj->getMeshID());

	gameRenderer.addToScene(*meshToRender->virtualModelID, *meshToRender->virtualTextureID, *meshToRender->virtualShaderID, &obj->transform.position,
		&obj->transform.scale, &obj->transform.rotate, &obj->transform.rotationAxis, &obj->transform.color);
	//    gameRenderer.draw(mesh.getMesh(obj->getMeshID()));

    //gameRenderer.settingModelMatrices(objects[1]->transform);
    //gameRenderer.draw(mesh.getMesh(objects[1]->getMeshID()));
    for (GameObject* child : obj->children) renderObjects(child, time);
}

/*
void GameObjects::FindIntersections(GameObject* obj, GameObject other)
{
    obj->IntersectWithObject(other);

    for (GameObject child : other)
    
    IntersectData intersect = obj->m_collider.IntersectSquare(objects[1]->m_collider, obj->intersects);

	IntersectData intersect = obj->m_collider.IntersectSquare(objects[1]->m_collider, obj->intersects);

	if (intersect.GetDoesIntersect())
	{
		obj->intersects = intersect.GetDistance();
		objects[0]->AdjustVelocity(intersect.GetDistance(), obj->intersects);
	}
	else {
		objects[0]->AdjustVelocity(0.0f, 0);
		obj->intersects = -1;
	}
    std::vector<IntersectData*> intersects;

    if (intersect.GetDoesIntersect() == true) intersects.push_back(&intersect);

    for (IntersectData* inter : intersects)
    {
        obj->intersects = intersect.GetCoordinate();
        objects[0]->AdjustVelocity(intersect.GetDistance());
    }

}
*/

/* work in process for checking multiple objects

void GameObjects::renderObjects(GameObject* obj, GLdouble time)
{
    Psuedo-code:

    1. check for intersectations with all objects that are aligned with the objects velocity

    2. 
    
    
    
    IntersectData intersect = obj->m_collider.IntersectSquare(objects[1]->m_collider, obj->intersects);

    obj->intersects = intersect.GetDistance();
    objects[0]->AdjustVelocity(intersect.GetDistance(), obj->intersects);

	//objects[0]->update(glm::vec3(0.f, 0.f, 0.f), time);
	obj->update(glm::vec3(0.f), time);
	//objects[0]->update(vel, time);
	//objects[1]->update(glm::vec3(0.f, 0.f, 0.f), time);
    objects[0]->update(time);

    objects[1]->update(time);

	auto meshToRender = mesh.getMesh(obj->getMeshID());

	//	gameRenderer.settingModelMatrices(obj->transform);
		// gameRenderer.draw(mesh.getMesh(obj->getMeshID()));
	gameRenderer.addToScene(*meshToRender->virtualModelID,*meshToRender->virtualTextureID,*meshToRender->virtualShaderID, &obj->transform.position,
		&obj->transform.scale, &obj->transform.rotate, &obj->transform.rotationAxis, &obj->transform.color);
		//gameRenderer.settingModelMatrices(objects[1]->transform);
		//  gameRenderer.draw(mesh.getMesh(objects[1]->getMeshID()));
	for (GameObject* child : obj->children) renderObjects(child, time);
}

*/

