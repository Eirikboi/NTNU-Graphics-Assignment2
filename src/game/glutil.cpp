#include "glutil.h"

#include <fstream>

#include <gfx.h>
/*



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

void create_debug_callback()
{
    glDebugMessageCallback(gl_debug_callback, nullptr);

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, true);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, true);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, true);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, false);
}
*/