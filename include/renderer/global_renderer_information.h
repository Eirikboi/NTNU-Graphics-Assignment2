#ifndef GLOBAL_RENDERER_INFORMATION_H
#define GLOBAL_RENDERER_INFORMATION_H


struct GlobalRenderInformation
{
private:
	//	static GameInput& instance;
	GlobalRenderInformation() {}
	GlobalRenderInformation(const GlobalRenderInformation& source) {}
	GlobalRenderInformation(GlobalRenderInformation&& source) {}
public:
	static GlobalRenderInformation& GetInstance()
	{
		//return instance;
		static GlobalRenderInformation instance;
		return instance;
	}
	int RENDERER_WINDOW_WIDTH;
	//Screen Height:
	int RENDERER_WINDOW_HEIGHT;

	const unsigned int SHADOW_WIDTH = 1024*4, SHADOW_HEIGHT = 1024*4;
	const glm::vec3 RENDERER_WORLD_STARTER_POSITION = glm::vec3(0.f, 0.f, 10.f);
	const glm::vec3 RENDERER_WORLD_DIRECTION_UP = glm::vec3(0.f, 1.f, 0.f);

};
#endif // !GLOBAL_RENDERER_INFORMATION_H


