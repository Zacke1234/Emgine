#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
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
#include "Memory.h"
#include "Collider.h"




#pragma once



int main()
{
	char* imageFile;
	
	
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Emgine", NULL, NULL);

	
	//std::cout << "" + a << std::endl;
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	Memory* myMemory = new Memory();

	Shader* myShader = new Shader("../Shader/VertexShader_1.glsl" ,"../Shader/FragmentShader_1.glsl");
	Lighting* myLighting = new Lighting();
	
	Camera* myCamera = new Camera();
	Texture* wallTex = new Texture("wall.jpg");
	Texture* myTexture = new Texture("Default 1.png");
	
	
	//myCollider->radius = 3;
	
	UI* myUI = new UI(window);
	ObjLoader* myObjLoader = new ObjLoader();

	myUI->objLoader = myObjLoader;

	MeshManager::Allocate();
	MeshManager* myMeshManager = &MeshManager::Get(); 
	
	Vertex myVertex{};
	
	//Mesh mesh;
	//std::shared_ptr<Mesh> aMesh = std::make_shared<Mesh>();
	Mesh mesh = myObjLoader->ObjParser("./fish.obj"); //teapot.obj / fish.obj
	
	Cube* Cubemesh = myMeshManager->GetCube();
	Cube* ObjMesh = myMeshManager->GetObject();

	Physics* Phys = new Physics();
	VirtualObject* VirtualObjectMesh{}; 
	VirtualObject* CubeVirtualObject{};
	VirtualObject* PlaneVirtualObject{};
	std::string name = "Mesh";
	std::string name2 = "Cube";
	
	// Initialization  
	Cubemesh->InitializeCube();
	//ObjMesh->InitializeObjectFile(&mesh);
	mesh.InitialiseMesh(&mesh);

 
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, myCamera->Mouse_Callback);

	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};

	
	glm::vec3 center = { 0, 0,0 }; float radius = 3; glm::vec3 pos = { 0,0,0 };
	// const glm::vec3& aCenter, const float& aRadius, glm::vec3 Apos
	SphereCollider* myCollider = new SphereCollider(center, radius, pos);
	

	// const glm::vec3& aCenter, const glm::vec3& someExtents
	glm::vec3 extents = { 0,0,0 };
	CubeCollider* cubeColl = new CubeCollider(center, extents);
	

	CubeVirtualObject = new VirtualObject(Cubemesh, myTexture, myShader, name2, cubeColl);
	PlaneVirtualObject = new VirtualObject(Cubemesh, myTexture, myShader, name2, cubeColl);

	//CubeVirtualObject->myCubeColl->isKinematic = false; //this dosen't work?

	PlaneVirtualObject->myCollider->isKinematic = true;
	PlaneVirtualObject->Scale = glm::vec3(7, 0.5f, 7);
	PlaneVirtualObject->Position = glm::vec3(1, 0, 1);

	VirtualObject::Entities.push_back(CubeVirtualObject);
	VirtualObject::Entities.push_back(PlaneVirtualObject);
	CubeVirtualObject->Position = glm::vec3(0, 10, 0);
	
	
	std::shared_ptr<Mesh> TeapotMesh = std::make_shared<Mesh>();
	
	while (VirtualObject::Entities.size() < 5) 
	{
		VirtualObjectMesh = new VirtualObject(&mesh, myTexture, myShader, name, myCollider);
		
		//myVirtualObject = new VirtualObject(&mesh, myTexture, myShader, name2);
		VirtualObject::Entities.push_back(VirtualObjectMesh);
		
		
		//VirtualObjectMesh->Position = glm::vec3(rand() % 20, rand() % 20, rand() % 20);
		VirtualObjectMesh->Position = glm::vec3(rand() % 5, 10, rand() % 5);
		
	}  
	
	float deltatime = 0.0f;
	float lastFrame = 0.0f;
	unsigned int depthMapFBO = 0;
	unsigned int depthMap = 0;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	//myLighting->Initialise();
	GLfloat BackgroundColor;
	myCamera->myPosition = glm::vec3(0, 3, 0);
	glEnable(GL_DEPTH_TEST);
	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		/*myCollider->position = VirtualObjectMesh->Position;
		myCollider->transform = VirtualObjectMesh->trans;*/
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

		

		// poll for and process events ?
		glfwPollEvents();

		
		myLighting->lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		myLighting->lightPos.y = (glfwGetTime() / 2.0f) * 1.0f;
		
		//Phys->Simulate(deltatime);
		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		myUI->RenderUI();

		myShader->UseShader();
		
		myLighting->Use(myCamera, myShader);

		Phys->Simulate(deltatime);
		//myVirtualObject->SetMesh(mesh);
		//smyLighting->Use();
		
		
		for (auto& o : VirtualObject::Entities)
		{		
			o->Draw(myCamera, myShader); // draws the cubes
			//o->DrawObject(myCamera, myShader); // draws the mesh from the file. for example, the teapot mesh
			
		}

		
		 
		
		VirtualObject::Entities[VirtualObject::SelectedEntity]->Position = glm::vec3(myUI->xPos, myUI->yPos, myUI->zPos);
		VirtualObject::Entities[VirtualObject::SelectedEntity]->Rotation = glm::vec3(myUI->xRot, myUI->yRot, myUI->zRot);
		VirtualObject::Entities[VirtualObject::SelectedEntity]->Scale = glm::vec3(myUI->xScale, myUI->yScale, myUI->zScale);
		
		myCamera->ProcessInput(window);
		
		myCamera->CameraUpdate(window);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// swaps front and back buffers
		glfwSwapBuffers(window);

		
		//glClearColor(0.7, 0.31, 0.9, 1);
	}
	  
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	myMemory->ClearMemory(myShader, Cubemesh, myCamera, myLighting, CubeVirtualObject, myUI, myMeshManager, &mesh, Phys, myCollider);
	delete myMemory;
	glfwTerminate();
	//std::cout << "hello engime" << std::endl;
	
	/*delete myShader;*/
	return 0;
}

