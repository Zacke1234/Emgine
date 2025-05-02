#pragma once
#include "MeshManager.h"
#include "VirtualObject.h"
#include "Physics.h"
#include "Camera.h"
#include "ObjLoader.h"
#include "Cube.h"



#pragma once
class UI
{
public:
	UI(GLFWwindow* window);
	void RenderUI(/*std::vector<VirtualObject*> objects, GLFWwindow* window*/);
	//ImGuiIO& io;

	float yPos = 0;
	float xPos = 0;
	float zPos = 0;

	float yRot = 0;
	float xRot = 0;
	float zRot = 0;

	float yScale = 1;
	float xScale = 1;
	float zScale = 1;
	char buf[255]{};
	char buf2[255]{};
	char buf3[255]{};
	char buf_Mesh[255];
	char buf_fov[2];
	float test[255];
	float step = 0;
	float step_fast = 0;

	int step2 = 1;
	int step2_fast = 100;

	char textureFile;

	char name;

	char charMesh;

	bool isCube;

	bool check;

	float fov = 70.0f;
	float speed = 10.0f;
	
	ObjLoader* objLoader;
private:

	Mesh* mesh;
	VirtualObject* virtobj;
	Shader* shade;
	Texture* texture;
	Camera* camera;
	CubeCollider* cubeCollider;
	Collider* newCollider;
	Physics* physics;
	MeshManager* meshmang;
	
};

