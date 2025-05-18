#pragma once
#include <stdio.h>
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Lighting.h"
#include "VirtualObject.h"
#include "UI.h"
#include <cstdlib>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Physics.h"
#include <mutex>
#include <thread>
#include <iostream>


class Memory
{
public:
	Memory();

	std::mutex* meshes;

	bool HasMemoryAvailable(int megaBytes);

	std::thread T1();

	void ClearMemory(Shader* myShader,
	Cube* myCube,
	Camera* myCamera,
	Lighting* myLighting,
	VirtualObject* virtObj,
	UI* myUI,
	MeshManager* myMeshManager,
	Mesh* ObjLoader,
	Physics* myPhysics,
	Collider* myCollider);

	void LoadInMemory(Shader* myShader,
		Cube* myCube,
		Camera* myCamera,
		Lighting* myLighting,
		VirtualObject* virtObj,
		UI* myUI,
		MeshManager* myMeshManager,
		Mesh* ObjLoader,
		Physics* myPhysics,
		Collider* myCollider);
private:
	Shader* myShader;
	Cube* myCube;
	Camera* myCamera;
	Lighting* myLighting;
	VirtualObject* virtObj;
	UI* myUI;
	MeshManager* myMeshManager;
	ObjLoader* ObjLoader;
	Physics* myPhysics;
	Collider* myCollider;
	Mesh* myMesh;
};

