
#include "Cube.h"
#include "VirtualObject.h"


#include <cassert>
#include "MeshManager.h"
#pragma once
MeshManager* MeshManager::instance = nullptr;
//VirtualObject* MeshManager::instance = nullptr; 
//Cube* cube = new Cube();
MeshManager::MeshManager() : Meshtest(std::make_unique<Mesh>()) // do init?
{
	
	// Ensure mesh is bufffered before rendered
}

void MeshManager::Allocate()
{
	assert(instance == nullptr); // once max ?
	if (instance) return;
	instance = new MeshManager();
}

MeshManager& MeshManager::Get()//Gets the singleton
{
	return *instance;
}

Cube* MeshManager::LoadCube()
{
	// checks if fromPath ends with .obj, exit if not
	Cube* newCube = new Cube();
	//newCube->Path = fromPath;
	// do .obj-loading here
	cubeList.push_back(newCube);
	return newCube;
}

Mesh* MeshManager::LoadMesh(std::string fromPath)
{
	/*std::string fullString = fromPath;
	std::string ending = ".obj";
	if (fromPath.length() >= ending.length())
	{
		return 0 (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{

		std::cout << "file must end with .obj";
	}*/
	Mesh* newMesh = new Mesh(myObjLoader->ObjParser(fromPath)); //teapot.obj / fish.obj
	//Mesh* newMesh = new Mesh();
	 

	meshList.push_back(newMesh);
	return newMesh;
}

