
#include "Cube.h"
#include <cassert>
#include "MeshManager.h"
#pragma once
MeshManager* MeshManager::instance = nullptr;
//VirtualObject* MeshManager::instance = nullptr; 
//Cube* cube = new Cube();
MeshManager::MeshManager()
{
	
	// Ensure mesh is bufffered before rendered
}

MeshManager::~MeshManager()
{
	for (auto& [key, value] : MeshCache)
	{
		delete value;
		
	}
	delete cube;
	delete myObjLoader;
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
	if (cube == nullptr)
	{
		cube = new Cube();
		cube->InitializeCube();
	}
	
	
	return cube;
}

Mesh* MeshManager::LoadMesh(std::string fromPath)
{
	if (MeshCache.find(fromPath) != MeshCache.end()) 
	{
		return MeshCache[fromPath];
	}
	else{
		Mesh* mesh = new Mesh();

		if (!myObjLoader->ObjParser(fromPath, mesh))
		{
			delete mesh;
			return nullptr;
		}

		mesh->InitialiseMesh();
		MeshCache.emplace(fromPath, mesh);

		
		return mesh;
	}
	
}

