#include "MeshManager.h"
#include <cassert>


#pragma once
MeshManager* MeshManager::instance = nullptr;

//
// 
// 
// 
// 
// 
// 
// * MeshManager::instance = nullptr; 
//Cube* cube = new Cube();
MeshManager::MeshManager()
{
	objLoader = new ObjLoader();
	std::cout << "Client triggers operation 1 (meshManager)" << "\n";
	/*c1->PerformMessage1();
	c2->PerformMessage4();
	c1->setMessage(message);*/
	// the order of all the calls and class calls matters alot 
	
	 

	// Ensure mesh is bufffered before rendered
}

MeshManager::~MeshManager()
{ 
	for (auto& [key, value] : MeshCache)
	{
		delete value;
		
	}
	delete cube;
	delete objLoader;
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
		msg = "Cube loaded in";
		//message->SendMessage(msg, 0);
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

		if (!objLoader->ObjParser(fromPath, mesh))
		{
			delete mesh;
			return nullptr;
		}

		msg = "Mesh loaded in";
		//message->SendMessage(msg, 0);
		mesh->InitialiseMesh();
		MeshCache.emplace(fromPath, mesh);

		
		return mesh;
	}
	
}

Mesh* MeshManager::Create(Mesh* myMesh)
{
	//myMesh->InitialiseMesh();
	return nullptr;
}

