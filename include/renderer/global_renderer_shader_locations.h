#ifndef GLOBAL_SHADER_LOCATIONS_H
#define GLOBAL_SHADER_LOCATIONS_H
//// NOTES ////
/*
	These locations are setup to always work in any shader for this program 
	because wer're using the same location in each shader.

	This file contains several locations to attributes, unifor and binding locations
	in the vertex and fragment shader. They are global because it is not recommended to
	glGetUniformLocation(...) for each time you need to access a location in the shaders:
*/

////   VERTICES	////

//VERTEX ATTRIBUTE:
#define VERTEX_POSITION_LOCATION	(unsigned)0
#define VERTEX_COLOR_LOCATION		(unsigned)1
#define VERTEX_TEXTURE_LOCATION		(unsigned)2
#define VERTEX_NORMAL_LOCATION		(unsigned)3
//MATRICES:
#define MATRIX_MODEL_LOCATION		(unsigned)0
#define MATRIX_VIEW_LOCATION		(unsigned)1
#define MATRIX_PROJECTION_LOCATION	(unsigned)2
#define MATRIX_NORMAL_LOCATION		(unsigned)3


////   TEXTURES	////
#define TEXTURE_UNIT_SAMPLER_LOCATION				(unsigned)1
#define TEXTURE_UNIT_ARRAY_SAMPLER_LOCATION			(unsigned)2
#define TEXTURE_ARRAY_LAYER_LOCATION				(unsigned)4
#define TEXTURE_SAMPLER_UNUSED_LAYER				(int)-1

////   LIGHT	////
#define TOTAL_LIGHT_SOURCES					(unsigned)16
#define LIGHT_UNIFROM_POSITION_LOCATION		(unsigned)11
#define LIGHT_UNIFORM_TOTAL_USED_LOCATION	(unsigned)5
#define LIGH_BLOCK_BINDING					(unsigned)2
//#define LIGHT_UNIFORM_NAME_COUNT			(unsigned)6
////	DIRECTIONAL LIGHT	////
#define	LIGHT_DIRECTIONAL_DIRECTION_LOCATION		(unsigned)7
#define LIGHT_DIRECTIONAL_COLOR_AMBIENT_LOCATION	(unsigned)8
#define LIGHT_DIRECTIONAL_COLOR_DIFFUSE_LOCATION	(unsigned)9
#define LIGHT_DIRECTIONAL_COLOR_SPECULAR_LOCATION	(unsigned)10
#define LIGHT_DIRECTIONAL_USE_LOCATION				(unsigned)6


////	SHADOWS		////
#define SHADOW_DIRECTIONAL_MODEL_MATRIX					(unsigned)19
#define SHADOW_DIRECTIONAL_LIGHT_SPACE_MATRIX			(unsigned)28
#define SHADOW_DIRECTIONAL_TEXTURE_SAMPLE_LOCATION		(unsigned)3
/*
static const GLchar* uniformLightNames[LIGHT_UNIFORM_NAME_COUNT] =
{
	"PointLights.constant",
	"PointLights.linear",
	"PointLights.quadratic",
	"PointLights.colorAmbient",
	"PointLights.colorDiffuse",
	"PointLights.colorSpecular"
};
static int pointLightIndices[LIGHT_UNIFORM_NAME_COUNT] {};
*/


#endif // !GLOBAL_SHADER_LOCATIONS_H
