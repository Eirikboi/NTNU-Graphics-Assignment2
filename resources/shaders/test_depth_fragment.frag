#version 450 core
out vec4 FragColor;
  
in vec2 texCoordsFrag;

layout(binding = 3) uniform sampler2D shadowSampler;

void main()
{             
    float depthValue = texture(shadowSampler, texCoordsFrag).r;
    FragColor = vec4(vec3(depthValue), 1.0);
} 