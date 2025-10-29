#pragma once
#include "MeshManager.h"
#include "Physics.h"
#include "Camera.h"
#include "MeshLoader.h"
#include "Managers/ObjectManager.h"
#include "Managers/ShaderManager.h"
#include "Managers/ColliderManager.h"
#include "Managers/TextureManager.h"
#include "Managers/LightingManager.h"
#include "Cube.h"
#include <Object.h>



#pragma once
class UI
{
public:
	enum ObjectType type;
	enum LightType lightType;
	UI(GLFWwindow* window);
	void RenderUI(ShaderManager* shader, ObjectManager* objectmanager);
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
	char textureBuffer[255]{};
	char textureNameBuffer[255]{};
	char nameBuffer[255]{};
	char buf3[255]{};
	char meshBuffer[255];
	char buf_fov[2];
	float test[255];
	float step = 0;
	float step_fast = 0;
	
	int step2 = 1;
	int step2_fast = 100;

	char textureFile;

	char name;

	char charMesh;

	bool check;

	float fov = 70.0f;
	float sens = 0.1f;
	float speed = 10.0f;
	
	MeshLoader* meshLoader;
private:

	Mesh* mesh;
	Object* virtobj;
	Shader* shade;
	Texture* texture;
	Camera* camera;
	CubeCollider* cubeCollider;
	Collider* newCollider;
	Physics* physics;
	LightData* newLightData;
	
	
	
};

