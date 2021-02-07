#version 450 core
#define TOTAL_LIGHTSOURCES 16
#define EPSILON 0.0000000000000001


////////////////    IN:
in VS_OUT {
    vec3        FragPointLightPositions[TOTAL_LIGHTSOURCES];    //Position of the light source
    flat int    FragUsedLightSources;                           //total amounts of lightsources supported
    vec3        FragDirection;
    vec2        FragTexCoord;
    vec3        FragNorm;
    vec3        FragactualVertexPosition;    //actual_vertex_position, Finding the actual position of the vertex in space for the fragment shader
    vec3        FragViewDirection;            //view_direction
    vec4        FragLightSpacePosition;
} fs_in;
////////////////    OUT:
out vec4 colorOut;




////////////////    STRUCTS:
////////    DIRECTIONAL LIGHT:
struct DirectionalLight {
    vec3 colorAmbient;  //Color of the ambient light in the scene
    vec3 colorDiffuse;  //Color of the diffuse light.
    vec3 colorSpecular; //Color of the specular light.
};  
////////    POINT LIGHT:
struct PointLight {
    float constant;     //offset 0.
    float linear;       //offset 4.
    float quadratic;    //offset 8.
    vec3 colorAmbient;  //offset 16.    Color of the ambient light in the scene
    vec3 colorDiffuse;  //offset 32.    Color of the diffuse light.
    vec3 colorSpecular; //offset 48.    Color of the specular light.
};
////////    MATERIAL:
struct Material {           //Not really used yet. I haven't had the time to look
    vec3 ambient;           //at what i can do with material. which is why it's hard
    vec3 diffuse;           //coded into this fragment shader.
    vec3 specular;
    float ambientStrenght;
    float diffuseStrenght;
    float specularStrenght;
    int specularSharpness;
}; 


////////////////    UNIFORMS:
////////    UNIFORM BLOCKS:
layout (std140, binding = 0) uniform PointLightBlock {
        PointLight pointLight[TOTAL_LIGHTSOURCES];
    } Light;
////////    UNIFORMS:
layout(location = 8)    uniform DirectionalLight directionalLight;
layout(location = 6)    uniform bool             useDirectionalLight = false;
                        uniform DirectionalLight dirLight;
                        uniform Material material;
////////    TEXTURES:
layout(binding = 1)     uniform sampler2D imageSampler;
layout(binding = 2)     uniform  sampler2DArray imageSamplerArray;
layout(location = 4)    uniform int imageSamplerArrayLayer = -1;
layout(binding = 3)     uniform sampler2D shadowSampler;




//calculateAmbience():
vec3 calculateAmbience (vec3 lightColor, float lightStrenght) 
{
    //Color times strenght:
    return lightStrenght * lightColor;
}

//calculateDiffuseLight():
vec3 calculateDiffuseLight(vec3 lightDirection, vec3 lightColor, float lightStrenght)
{
    //Maxing because we can't have a light below 0,
    //We're just picking the higest number so it can't be lower than 0
    //so diffusion will be between 0 and 1:
    float diffusion = max(0.0, dot(normalize(fs_in.FragNorm), lightDirection));
    return diffusion * lightColor;
}

//calculateSpecularLight():
//NOTE! Light direction is pointing away from the surface and torwards the lightsrource.
//NOTE Sharpness and specularity has to be aboce 0:
vec3 calculateSpecularLight(vec3 lightPosition, vec3 lightDirection, vec3 lightColor,  int specularSharpness, float lightStrenght)
{
    //Finding the reflecting light direction of the current light direction:
    vec3 reflectionDirection = reflect(normalize(lightDirection), normalize(fs_in.FragNorm));
    //Maxing becaus we can't have a light below 0,
    //We're just picking the higest number so it can't be lower than 0:
    //NOTE! And setting the dot product (which can only be 0 - 1, because they are both the lenght 1) to the power of 32.
    //this means that the higher the int, sharpness, is the smaller the specilar points will be:
    float spec_power = pow(max(0.0, dot(fs_in.FragViewDirection, reflectionDirection)), specularSharpness);
    return lightStrenght * spec_power *  lightColor;
}

//calculateAttenuation():
//lightPosition' worldspace position
float calculateAttenuation(vec3 lightPosition, float constant, float linear, float quadratic)
{
    // Attenuation
    float distance = length(lightPosition - fs_in.FragactualVertexPosition);
    //returning:
    return 1.0 / (constant + linear * distance + quadratic * distance * distance + EPSILON);
}

float calculateShadow(vec4 position) 
{
    //Code taken from: https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping:
    // perform perspective divide
    vec3 projCoords = fs_in.FragLightSpacePosition.xyz / fs_in.FragLightSpacePosition.w;
        if(projCoords.z > 1.0)
    return 0.0;

    projCoords = projCoords * 0.5 + 0.5; 
    float closestDepth = texture(shadowSampler, projCoords.xy).r;   
    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(fs_in.FragNorm, fs_in.FragDirection)), 0.0005);  
//    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowSampler, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowSampler, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    return shadow;
}


////////    POINT LIGHT:
vec3 calculatePointLight(
    vec3 pointLightPosition,
	PointLight thisPointLight,	//The light
    Material thisMaterial       //The material
)
{
    //Light direction is pointing away from the surface and torwards the lightsrource.
    vec3 lightDirection = normalize(pointLightPosition - fs_in.FragactualVertexPosition);
    vec3 ambient = calculateAmbience(thisPointLight.colorAmbient,
        thisMaterial.ambientStrenght )  * thisMaterial.ambient;
    //Calculating diffuse light:
    vec3 diffuse = calculateDiffuseLight(lightDirection, thisPointLight.colorDiffuse,
        thisMaterial.diffuseStrenght) * thisMaterial.diffuse; 
    //Calculating specular light:
    vec3 specular = calculateSpecularLight(pointLightPosition, lightDirection,
        thisPointLight.colorSpecular, thisMaterial.specularSharpness,
        thisMaterial.specularStrenght) * thisMaterial.specular;   
    //calculate the attenuation:
    float attenuation = calculateAttenuation(pointLightPosition, thisPointLight.constant, thisPointLight.linear, thisPointLight.quadratic);
    return (ambient + diffuse + specular * attenuation);
}

////////    DIRECTIONAL LIGHT:
vec3 calculateDirectionalLight(
    DirectionalLight thisDirectionalLight,
    Material thisMaterial
) //will calculate the directional light (if there is one)
//vec3 calculateDirectionLight(DirLight light, vec3 normal, vec3 viewDir) 
{
    vec3 lightVector = normalize(-fs_in.FragDirection);
    // diffuse shading:
    float diff = max(dot(fs_in.FragNorm, lightVector), 0.0);
    // specular shading:
    vec3 reflectDir = reflect(-lightVector, fs_in.FragNorm);
    float spec = pow(max(dot(fs_in.FragViewDirection, reflectDir), 0.0), 
        material.specularSharpness);
    //combine results:
    vec3 ambient  = thisDirectionalLight.colorAmbient *
        thisMaterial.ambientStrenght * thisMaterial.ambient;//  * vec3(texture(thisMaterial.diffuse, tex_coord));
        //Calculating diffuse light:
    vec3 diffuse = calculateDiffuseLight(lightVector, 
        thisDirectionalLight.colorDiffuse, thisMaterial.diffuseStrenght) *
        thisMaterial.diffuse; 
//    return (ambient + diffuse);// + specular);
  // calculate shadow
    float shadow = calculateShadow(fs_in.FragLightSpacePosition);       
//    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + spec));    
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse));    
    return lighting;
}








void main()
{   
//HARDCODED MATERIAL SINCE WE DON*T USE IT YET:
Material m;
m.specularSharpness = 64;
m.ambientStrenght = 0.5;
m.diffuseStrenght = 2;
m.specularStrenght = 2;
m.ambient = vec3(0.5);
m.diffuse = vec3(1);
m.specular = vec3(1);




vec3 resultLight = vec3(0); //resultColor will be the resulting color after calculating all the light sources:
if (fs_in.FragUsedLightSources > 0) {
        for(int i = 0; i < fs_in.FragUsedLightSources; i++)
    {
     //   resultLight += calculatePointLight(pointLightPositions[i],pp[0], m);
        resultLight += calculatePointLight(fs_in.FragPointLightPositions[i],Light.pointLight[i], m);
    }
}
if(useDirectionalLight)
{
    resultLight += calculateDirectionalLight(directionalLight, m);
}
if(!useDirectionalLight && fs_in.FragUsedLightSources < 0)
{
    resultLight = vec3(1);    
}
    //If the texture is an animated sprite:
    if (imageSamplerArrayLayer > -1)
    {
        //Spritesheet:
//        color_out= /*vec4(spriteColor, 1.0) */ vec4(texture(imageSamplerArray,vec3(tex_coords.x,tex_coords.y,image_sampler_array_layer)).rgb * resultLight, 1.0);
    } else {
        vec4 tex = texture(imageSampler, fs_in.FragTexCoord);
        colorOut= /*vec4(spriteColor, 1.0) */ vec4(tex.rgb * resultLight, tex.a);
    }
    //If the texture is transparent the values below this shouldn't be visible:
    if(colorOut.a < 0.1) 
    {
    discard;
    }
}
