#pragma once
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Lighting.h"
#include "VirtualObject.h"
#include "UI.h"
#include <stdio.h>
#include <cstdlib>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "MeshManager.h"
#include "ObjLoader.h"
#include "Physics.h"
#include "Collider.h"

class Memory
{
public:
	Memory();
	bool HasMemoryAvailable(int megaBytes);

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

