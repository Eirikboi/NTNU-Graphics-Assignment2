#include <game_application.h>

GameApplication::GameApplication()
{
	//Initialize window:
	initializeGlfwGlWindow();
	initializeInputCallbacks();
	create_debug_callback();

	imguiInitialize();
	//Initialize everythin else if succeeded:
	if (gameWindow) this->gameObjects.initializeEverything();
}

GameApplication::~GameApplication()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(this->gameWindow);
	glfwTerminate();
}

void GameApplication::initializeGlfwGlWindow()
{ // Initialise GLFW
	if (!glfwInit())
	{
		GFX_ERROR("Failed to initialize GLFW\n");
		return;
	}
	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);         // Change to 5 if you want to use modern features! :D
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // To allow debug callbacks
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	gameWindow = glfwCreateWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, "Assignment 1", nullptr, nullptr);
	if (gameWindow == nullptr)
	{
		GFX_ERROR("Failed to open GLFW window.\n");
		return;
	}

	glfwMakeContextCurrent(gameWindow);

	// Initialize Glad
	if (!gladLoadGL())
	{
		GFX_ERROR("Failed to initialize GLAD\n");
	}

	glfwSetInputMode(gameWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(1);
	//Set color to annoying purple:
	glClearColor(0.6f, 0.7f, 0.95f, 1.f);

	//enabling depth:
	glEnable(GL_DEPTH_TEST);
	return;
}

//Runs the entire game loop, wether the game is paused or running, everything goes through here:
void GameApplication::gameRunLoop()
{
	// change fps
	//MS_PER_UPDATE = 0.008f;

	while (!glfwWindowShouldClose(this->gameWindow)) // true
	{
		//---------------------------------------------------
		elapsed = glfwGetTime();
		deltaTime = elapsed - previous;
		previous = elapsed;
		this->currentFPS += deltaTime;
		//-----------------------------------------------------

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//processInput();

		//UI
		ui();
		if (!imguiShowMenu)
		{
			// exstra fps will used on exstra update
			while (currentFPS >= MS_PER_UPDATE)
			{
				// If UI is not displayed
				gameUpdate(); //  AI and physics
				currentFPS -= MS_PER_UPDATE;

			}
			render(currentFPS / MS_PER_UPDATE, elapsed);
		}
		glfwSwapBuffers(this->gameWindow);
		glfwPollEvents();
	}
}
//IU
void GameApplication::ui()
{
	if (this->imguiShowMenu || glfwGetKey(this->gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// Show mouse
		glfwSetInputMode(this->gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		this->imguiShowMenu = true;
		//imgui:
		imguiUpdate();
	}
	else
	{
		// DISABLED mouse = reset rotation
		glfwSetInputMode(this->gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
//Runs for everytime the game should update. Updates all the gameobjects informations:
void GameApplication::gameUpdate()
{	                                                      //timeLastFrame
	this->gameObjects.update(gameWindow, this->deltaTime, this->elapsed);
}

//Shoul reset the entire game to its initial starting state:
void GameApplication::gameReset()
{

}

void GameApplication::render(GLdouble timeSinceLastFrame, GLdouble time)
{
	this->gameObjects.render(timeSinceLastFrame, this->elapsed);
}

#ifndef WIN32
#    define APIENTRY
#endif
void gl_debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW: GFX_INFO(message); break;
	case GL_DEBUG_SEVERITY_MEDIUM: GFX_WARN(message); break;
	default: GFX_WARN(message); break;
	}
}
void GameApplication::create_debug_callback()
{
	glDebugMessageCallback(gl_debug_callback, nullptr);

	//Only enable LOW -> HIGH priority debug messages. Ignore Notifications
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, false);
}
