#include <stdio.h>
#include "imgui.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Camera.h"
#include "Lighting.h"
#include "string"
#include <cstdlib>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "Object.h"
#include "UI.h"
#include "MeshManager.h"
#include "MeshLoader.h"
#include "Physics.h"
#include "Memory.h"
#include "Collider.h"
#include "Message.h"
#include "Threading.h"
#include "Observer.h"
#include <float.h>
#include <thread>
#include <mutex>
#include <Managers/ColliderManager.h>
#include <Managers/ObjectManager.h>
#include <Managers/ShaderManager.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Managers/ObjectManager.h>
#include <Managers/TextureManager.h>
#include "../DisplayMessage.h"



using namespace std;
#pragma once


GLFWwindow* window;
//Threading* myThread = new Thread(); 
//Shader* myShader;
Lighting* myLighting;
Camera* myCamera;
MeshManager* myMeshManager;
ObjectManager* myObjectManager;
ShaderManager* myShaderManager;
ColliderManager* MyColliderManager;
TextureManager* myTextureManager;
Memory* myMemory;
MeshLoader* myMeshLoader = nullptr;
//UI* myUI;
Message* myMessage;
CubeCollider* cubeColl;


int message_stuff() {
	myMessage = new Message;

	DisplayMessage displayMessage1;
	DisplayMessage displayMessage2;

	myMessage->Attach(&displayMessage1);
	myMessage->Attach(&displayMessage2);

	myMessage->setMessage("Mesh loaded");
	myMessage->setMessage("Object loaded");
	return 0;
}


//Init Functions

int static init_window()
{
	if (!glfwInit())
	{

		std::cout << "Failed to initialize glfw" << endl;
		//myMessage->SendMessage(message, 0);
		return -1;
	}
	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;

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
		//message = "Failed to initialize GLAD";
		std::cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	return 0;
}

int init_memory_tracker() {
	int megaBytes = 0;
	myMemory = new Memory();
	myMemory->HasMemoryAvailable(megaBytes);
	return 0;
}

int init_managers() {

	myMeshManager = new MeshManager();

	myTextureManager = new TextureManager();
	//TODO: init shader, collider, and rigidbodymanager
	myObjectManager = new ObjectManager();
	return 0;
}

int init_camera() {
	//init camera
	myCamera = new Camera();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, myCamera->Mouse_Callback);
	return 0;
}

int init_colliders() {
	glm::vec3 extents = { 1,1, 1 };
	glm::vec3 extentsPlane = { 7 / 2, 0.5f / 2, 7 / 2 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	cubeColl = new CubeCollider(center, extents, pos);
	return 0;
}

int init_lightning() {
	//init shader/lighting
	glm::vec3 PointLight1;
	glm::vec3 DirectionalLight1;
	glm::vec3 SpotLight;
	//myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	myLighting = new Lighting();
	return 0;
}

int init_physics() {
	//init physics
	//Phys = new Physics();
	float deltatime = 0.0f;
	float lastFrame = 0.0f;
	unsigned int depthMapFBO = 0;
	unsigned int depthMap = 0;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	return 0;
}


// Update Functions

int static update_camera(Camera* cam, /*UI* myUI,*/ GLFWwindow* window)
{
	cam->ProcessInput(window);
	cam->CameraUpdate(window);
	cam->fieldOfView = 70;
	cam->sensitivity = 0.1f;
	/*cam->fieldOfView = myUI->fov;
	cam->sensitivity = myUI->sens;*/
	return 0;
}

int static update_ui(UI* myUI, Shader* myShader)
{
	myUI->RenderUI(myShader);
	
	Object::Entities[Object::SelectedEntity]->Position = glm::vec3(myUI->xPos, myUI->yPos, myUI->zPos);
	Object::Entities[Object::SelectedEntity]->Rotation = glm::vec3(
		glm::radians(myUI->xRot),
		glm::radians(myUI->yRot),
		glm::radians(myUI->zRot));
	Object::Entities[Object::SelectedEntity]->Scale = glm::vec3(myUI->xScale, myUI->yScale, myUI->zScale);
	
	return 0;
}




int main()
{
	init_window();

	init_memory_tracker();

	init_managers();

	init_camera();
	myCamera->myPosition = glm::vec3(0, 3, 0);

	//Create Textures
	Texture* wall = myTextureManager->Create("Wall", "wall.jpg");
	myTextureManager->Create("Default", "Default 1.png");

	//Create Meshes

	Mesh* fish = myMeshManager->Create("fish", "fish.obj");

	init_colliders();

	init_lightning();
	
	myShaderManager->InitDefaultShader();
	
	//myUI = new UI(window);


	// Object Creation


	myObjectManager->Create(
		"fishObj",
		fish,
		wall,
		myShaderManager->DefaultShader,
		MyColliderManager->Create(cubeColl)
	);




	glEnable(GL_DEPTH_TEST);
	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

		
		//myThread->DoWork(deltatime);
		
		// poll for and process events ?
		glfwPollEvents();

		//myMemory->LoadInMemory(myShaderManager->DefaultShader, myCamera, myLighting, myObjectManager, myUI, myMeshManager, fish, cubeColl);

		
		
		
		//if (Phys->TimeTicking)
		//{
		//	double currentFrame = glfwGetTime();
		//	deltatime = currentFrame - lastFrame;
		//	lastFrame = currentFrame;
		//	//Phys->Simulate(deltatime);
		//}
		
		

		myShaderManager->DefaultShader->UseShader();
		
		
		//messageUI->RenderUI();
		myLighting->Use(myCamera, myShaderManager->DefaultShader);
		
	

		/*for (auto& c : Collider::)
		{
			c->SetTheCollision();
		}*/

		
		//Drawcall objects
		for (auto& o : Object::Entities)
		{
			
			o->Draw(myCamera, myShaderManager->DefaultShader); // draws the cubes
			
		}
		
		// render UI (after/ON TOP OF drawcall)
		//update_ui(myUI, myShaderManager->DefaultShader);

		//update camera
		update_camera(myCamera, /*myUI,*/ window);
		

		/*ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/


		// swaps front and back buffers
		glfwSwapBuffers(window);

		
		//glClearColor(0.7, 0.31, 0.9, 1);
	}
	  
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//myMessage->~Message();
	//myMemory->ClearMemory(myShaderManager->DefaultShader, myCamera, myLighting, myObjectManager, myUI, myMeshManager, MeshMesh, cubeColl);
	//delete myMemory;
	glfwTerminate();
	//std::cout << "hello engime" << std::endl;
	
	/*delete myShader;*/
	return 0;
}







