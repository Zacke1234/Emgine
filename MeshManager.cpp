
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
	// on string input set entity cube in UI
	//cubeList = new std::list<Cube*>();
	//virtualObj = new VirtualObject();
	/*Cube* cube = this->GetCube("Path");
	if (cube == nullptr)
		cube = this->LoadCube("Path");*/
	cube = new Cube();

	ObjectMesh = new Cube();

	
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

Cube* MeshManager::GetCube()
{
	return cube;
}

Cube* MeshManager::GetObject()
{
	return ObjectMesh;
}

Cube* MeshManager::LoadCube()
{
	// checks if fromPath ends with .obj, exit if not
	Cube* newCube = new Cube();
	//newCube->Path = fromPath;
	// do .obj-loading here
	cubeList->push_back(newCube);
	return newCube;
}

