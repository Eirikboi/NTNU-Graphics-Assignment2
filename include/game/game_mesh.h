#ifndef GAME_MESH_H
#define GAME_MESH_H


#include <struct_transform.h>
#include <string>
#include <vector>
#include <global_game_variables.h>

// Offset
struct MeshData
{
	
	int *virtualShaderID;
	int *virtualTextureID;
	int *virtualModelID;
};

class Mesh 
{
public:
	Mesh();
	~Mesh();
	void initiateHardcodedDummyList();
	void render(int ID, Transform tr);
	MeshData* getMesh(int ID);
	void addMesh(int * virtualMeshID);
	//void addTexturePath(std::string virtualTexture, std::string virtualObject);
//	int decypherID(std::string ID);
	
	//TransformList tList = TransformList();
	std::vector<MeshData> meshDatas;
	int* allocateModelID() { 
		//this->virtualModelsds.push_back(0);
		totalVirtualModelsIds++;
		return &this->virtualModelsds[totalVirtualModelsIds-1];
	};
	int* allocateTextureID()
	{
		//	this->virtualTexturesIds.push_back(0);
		totalVirtualTexturesIds++;
		return &this->virtualTexturesIds[totalVirtualTexturesIds-1];
	};
	int* allocateShaderID()
	{
		totalVirtualShadersIds++;
//		this->virtualShadersIds.push_back(0);
		return &this->virtualShadersIds[totalVirtualShadersIds-1];
	};
protected:

private:
	//This is where all the virtual textures ID:
	std::vector<int> virtualTexturesIds = std::vector<int>(MAX_TOTAL_VIRTUAL_TEXTURES);

	//This is where all the virtual model ID:
	std::vector<int> virtualModelsds = std::vector<int>(MAX_TOTAL_VIRTUAL_MODELS);
	//This is where all the virtual shader ID:
	std::vector<int> virtualShadersIds = std::vector<int>(MAX_TOTAL_VIRTUAL_SHADERS);
	int totalVirtualModelsIds{};
	int totalVirtualTexturesIds{};
	int totalVirtualShadersIds{};

	std::vector<int*> meshHandles{};

	//Renderer gameRenderer{};

};
#endif //!GAME_MESH_H