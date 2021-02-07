#ifndef GL_ERROR_HANDLING_H
#define GL_ERROR_HANDLING_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
				  x;\
				ASSERT(GLLogErrorCall(#x, __FILE__, __LINE__))


static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogErrorCall(const char* function , const char* file, int line) {
	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") function: " << function << "\n file: " << file << "\n line:" << line << "\n";
		return false;
	}
	return true;
}

#endif // !GLERRORHANDLING_H
