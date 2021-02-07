#include <game_mesh.h>
#include <renderer.h>

//Renderer gameRenderer{};

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    for (auto i : meshHandles)
    {
        delete i;
    }
}

void Mesh::initiateHardcodedDummyList()
{
}

MeshData* Mesh::getMesh(int ID)
{
    return &meshDatas[ID];
}

void Mesh::addMesh(int * virtualMeshID) 
{

    if (*virtualMeshID>0)
    {
        std::cout << "addMesh() failed because the virtualMeshID is already in use\n";
        return;
    }
    //size is the ID of the mesh:
    auto meshHandleID = meshDatas.size();
    this->meshHandles.push_back(virtualMeshID);
    //Setting the id for the meshHandle:
  //  this->meshHandles[meshHandleID] = new int;
    *this->meshHandles[meshHandleID] = meshHandleID;
    meshDatas.push_back(MeshData());
    //returns the address of the last meshdata:
}

