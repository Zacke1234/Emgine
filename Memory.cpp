#include "Memory.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

Memory::Memory()
{

}

bool Memory::HasMemoryAvailable(int megaBytes)
{

	return false;
	
}

void Memory::ClearMemory(Shader* CmyShader, Cube* CmyCube, Camera* CmyCamera, Lighting* CmyLighting, VirtualObject* CvirtObj, UI* CmyUI, MeshManager* CmyMeshManager, Mesh* CObjLoader, Physics* CmyPhysics, Collider* CmyCollider)
{
	myShader = CmyShader;
	delete CmyShader;
	myCube = CmyCube;
	delete CmyCube;
	myCamera = CmyCamera;
	delete CmyCamera;
	myLighting = CmyLighting;
	delete CmyLighting;
	virtObj = CvirtObj;
	delete CvirtObj;
	myUI = CmyUI;
	delete CmyUI;
	myMeshManager = CmyMeshManager;
	delete CmyMeshManager;
	myMesh = CObjLoader;
	delete CObjLoader;
	myPhysics = CmyPhysics;
	delete CmyPhysics;
	myCollider = CmyCollider;
	delete CmyCollider;
	/*for (auto& o : VirtualObject::Entities)
	{
		
	}*/
	
}

