#include <game_user_interface.h>

// xxx delete script
UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}


void UserInterface::imguiInitialize(GLFWwindow * window, GLuint width, GLuint height)
{
	if (this->gameWindow)
	{
		this->windowHeight = height;
		this->windowWidth = width;
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(gameWindow, true);
		ImGui_ImplOpenGL3_Init("#version 430 core");
	}
}

void UserInterface::imguiUpdate()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	imguiStarterWindow();

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(gameWindow, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

bool UserInterface::imguiStarterWindow()
{
	//Pushing background color:
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(0, 0, 0, 255)));
	//Variables:
	static float f = 0.0f;
	static int counter = 0;
	static int other_counter = 0;
	bool show = true;
	//Position of the window:
	ImVec2 pos = ImVec2(0.f, 0.f);
	//Size of the window:
	const ImVec2 size = ImVec2(this->windowWidth, this->windowHeight);


		static bool lightGreen = false;

	//	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui::Begin("start_window!", false, ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowPos(pos, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.f);
	//	ImGui::ColorEdit4(ImGuiColorEditFlags_AlphaBar,ImGuiColorEditFlags_)
	ImGui::GetStyle().WindowRounding = 0.f;
	ImGui::GetStyle().Alpha = 1.f;
	ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Right;


	ImGui::SetWindowSize(size, ImGuiCond_Once);


		

	const auto buttonStartGameID = "start_new_game";

	const auto size_x = ImGui::GetWindowSize().x / 4;
	const auto size_y = ImGui::GetWindowSize().y / 8;

	const auto pos_x = ImGui::GetWindowSize().x / 2 - (size_x / 2);
	const auto pos_y = ImGui::GetWindowSize().y / 2 - (size_y / 2);

	const auto padding_y = size_y / 8;
	// xxx
	//ImGui::SetCursorScreenPos(ImVec2(pos_x + 10, pos_y));
	//if (ImGui::Button("HEi:", ImVec2(size_x + 10, size_y)))
	//{
	//	//
	//	counter++;
	//	return false;
	//}
	// xxx
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::SetCursorScreenPos(ImVec2(pos_x, pos_y));
	if (ImGui::Button("Start New Gameasdf:", ImVec2(size_x, size_y)))
	{
		//
		counter++;
		return false;
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	// Buttons return true when clicked (most widgets return true when edited/activated):
	//ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos(ImVec2(pos_x, pos_y - size_y - padding_y));
	if (ImGui::Button("Scoreboardasdasxxx:", ImVec2(size_x, size_y)))
	{
		//
		unsigned windowWidth{};
		counter++;
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	// Buttons return true when clicked (most widgets return true when edited/activated):
	ImGui::SetCursorScreenPos(ImVec2(pos_x, pos_y + size_y + padding_y));
	if (ImGui::Button("Settings:", ImVec2(size_x, size_y)))
	{
		//gameIsPaused = (gameIsPaused == false) ? true : false; xxxEi
		if (gameIsPaused == false)
		{
			gameIsPaused = true;
			return true;
		}
		else { 
			gameIsPaused = false; 
			return false; 
		}
	
		other_counter++;
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", other_counter);

	ImGui::Checkbox("PauseGame", &gameIsPaused);
	ImGui::Checkbox("GreenLight", &gameIsPaused); // xxx

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//ImGui::Checkbox("Demo Window", &show);      // Edit bools storing our window open/close state
	//ImGui::Checkbox("Another Window", &show);



	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::PopStyleColor(1);
	ImGui::End();
}