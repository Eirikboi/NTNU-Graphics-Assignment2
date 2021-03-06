#version 450 core
layout (location = 0) in vec3 position;

layout (location = 28) uniform mat4 lightSpaceMatrix;
layout (location = 19) uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(position, 1.0);
}  