#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
//ImGui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
//#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gfx.h>

class UserInterface
{
public:
	/////////////IMGUI
	// xxx delete script
	void imguiUpdate();
	void imguiInitialize(GLFWwindow* window, GLuint width, GLuint height);
	bool imguiStarterWindow();

	UserInterface();
	~UserInterface();

private:
	GLFWwindow* gameWindow;
	bool gameIsPaused = false;
	unsigned windowWidth{};
	unsigned windowHeight{};
};


#endif // !USERINTERFACE_H
