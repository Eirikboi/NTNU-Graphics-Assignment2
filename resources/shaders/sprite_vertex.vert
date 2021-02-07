//#version 450 core
//
//layout (location = 0)in vec3 position;     
//layout (location = 1)in vec3 color;
//layout (location = 2)in vec2 uv_coord;
//layout (location = 3)in vec3 normal;    
//
//out vec2 tex_coords;
////actual_vertex_position, Finding the actual position of the vertex in space for the fragment shader
////and its lighting:
//out vec3 actual_vertex_position;
////view_direction
//out vec3 view_direction;
//out vec3 norm;
//layout (location = 0) uniform mat4 model = mat4(1);
//layout (location = 1) uniform mat4 view = mat4(1);
//layout (location = 2) uniform mat4 projection = mat4(1);
////lighting:
//
//uniform mat3 normal_matrix = mat3(1); // This will be used to calculate our normals in eye space
//
//void main()
//{
//    norm = normalize(normal_matrix * normalize(normal));
//    tex_coords = uv_coord;
//    //Finding the actual position of the vertex in space for the fragment shader
//    //and its lighting:
//    actual_vertex_position = vec3(model * vec4(position, 1.0));
//    //calculating the view_direction to the actual vertex:
//    view_direction = normalize(vec3(inverse(view) * vec4(0,0,0,1) - model * vec4(position, 1.0)));
//    gl_Position  = projection * view * model * vec4(position,1.0);	
//}
//





#version 450 core
//total amounts of lightsources supported:
#define TOTAL_LIGHTSOURCES 16

layout (location = 0)in vec3 position;
layout (location = 1)in vec3 color;
layout (location = 2)in vec2 uvCoord;
layout (location = 3)in vec3 normal;  
//in vec3 position;     
//layout (location = 1)in vec3 color;
//in vec2 uv_coord;
//in vec3 normal;    
//


    
//UNIFORM:
layout (location = 0)   uniform mat4    model           = mat4(1);
layout (location = 1)   uniform mat4    view            = mat4(1);
layout (location = 2)   uniform mat4    projection      = mat4(1);
layout (location = 3)   uniform mat3    normalMatrix    = mat3(1);  //normal matrix used to calculate our normals in eye space.
layout (location = 28)  uniform mat4    lightSpaceMatrix;           //Lightspace mat. used for shadows.
//lighting NOTE: LOCATIONS FROM 10 - 74 are occupied:
layout(location = 6)    uniform bool    useDirectionalLight = false;
layout(location = 7)    uniform vec3    directionalLightDirection;// = vec3(0,-1,0);             //The direction of the light. Doesn't matter where it comes from.
layout (location = 5)   uniform int     usedLightSources = 0;
//layout (location = 10) uniform int usedLightSources = 1;
//setPointLightPosition location: 12 - 27.
layout (location = 12)  uniform vec3    setPointLightPosition[TOTAL_LIGHTSOURCES];            //Position of the light source
//layout (location = 11) uniform vec3 setPointLightposition[TOTAL_LIGHTSOURCES];              //Position of the light source
layout (location = 11)  uniform int     usedLightSourcess = 1;

out VS_OUT {
    vec3        FragPointLightPositions[TOTAL_LIGHTSOURCES];              //Position of the light source
    flat int    FragUsedLightSources;
    vec3        FragDirection;
    vec2        FragTexCoord;
    vec3        FragNorm;
    vec3        FragactualVertexPosition;    //actual_vertex_position, Finding the actual position of the vertex in space for the fragment shader
    vec3        FragViewDirection;            //view_direction
    vec4        FragLightSpacePosition;
} vs_out;

//out vec4 vertPosition;
void main(void)
{
    vs_out.FragNorm = normalize(normalMatrix * normalize(normal));
    vs_out.FragTexCoord = uvCoord;
    //Finding the actual position of the vertex in space for the fragment shader
    //and its lighting:
    vs_out.FragactualVertexPosition = vec3(view * model * vec4(position, 1.0));
    //calculating the point light position in camera space:
    for(int i = 0; i < usedLightSources; i++)
    {
        vs_out.FragPointLightPositions[i] = (view * vec4(setPointLightPosition[i], 1)).xyz;
    }

    if(useDirectionalLight)
    {
        vs_out.FragDirection = (view * vec4(directionalLightDirection, 0)).xyz;
    }
    vs_out.FragUsedLightSources = usedLightSources;
    //calculating the view_direction to the actual vertex:
    vs_out.FragViewDirection = normalize(vec3(inverse(view) * vec4(0,0,0,1) - model * vec4(position, 1.0)));
    vs_out.FragLightSpacePosition = lightSpaceMatrix * vec4(model * vec4(position, 1.0));
 
	//vertPosition = vec4(position,1.0);
    gl_Position  = projection * view * model * vec4(position,1.0);	
}
