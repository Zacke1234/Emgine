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
#include <Managers/LightingManager.h>



using namespace std;
#pragma once


GLFWwindow* window;

Lighting* myLighting;
Camera* myCamera;
MeshManager* myMeshManager;
ObjectManager* myObjectManager;
ShaderManager* myShaderManager;
ColliderManager* MyColliderManager;
TextureManager* myTextureManager;
Memory* myMemory;
MeshLoader* myMeshLoader = nullptr;
UI* myUI;
Message* myMessage;
MessageQueue* myMessageQueue;
CubeCollider* cubeColl;
SphereCollider* sphereColl;
LightingManager* myLightingManager;
//Threading* myThreading;
Thread* myThread; 
LightData* myLightData;


int message_stuff() { // message passing between meshmanager and objectmanager
	myMessage = new Message;
	myMessageQueue = new MessageQueue;

	myThread = new Thread();
	//myThread->DoWork(myMeshManager, myMessage);
	//myMessage->setMessage("Thread started for MeshManager");
	

	myMessage->Attach(myMeshManager);
	myMessage->setMessage(myObjectManager->message = "MeshManager attached to ObjectManager (Subject)"); // Subject attaches to Observer, because the observer observes the subject

	myMessage->setMessage("Queue the message");
	myMessageQueue->Enqueue(myMessage);
	
	

	myMessage->setMessage("Detach MeshManager from Message");
	myMessage->setMessage("Dequeue the message");
	myMessage->Detach(myMeshManager);
	myMessageQueue->Dequeue(myMessage);
	
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
	
	myLightingManager = new LightingManager();
	myMeshManager = new MeshManager;
	myShaderManager = new ShaderManager();
	myTextureManager = new TextureManager();
	MyColliderManager = new ColliderManager();
	
	//TODO: init shader, collider, and rigidbodymanager
	myObjectManager = new ObjectManager;
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
	sphereColl = new SphereCollider(center, radius, pos);
	return 0;
}

int init_lightning() {
	//init shader/lighting
	glm::vec3 PointLight1;
	glm::vec3 DirectionalLight1;
	glm::vec3 SpotLight;
	//myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	myLighting = new Lighting();
	myLightData = new LightData();
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

int static update_camera(Camera* cam, UI* myUI, GLFWwindow* window)
{
	cam->ProcessInput(window);
	cam->CameraUpdate(window);
	
	cam->fieldOfView = myUI->fov;
	cam->sensitivity = myUI->sens;
	return 0;
}

int static update_ui(UI* myUI, ShaderManager* myShader, ObjectManager* objManager)
{
	myUI->RenderUI(myShader, objManager);
	
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
	
	//Message calling
	message_stuff();
	

	

	init_colliders();

	init_lightning();
	
	myShaderManager->InitDefaultShader();
	
	myUI = new UI(window);

	
	// Object Creation
	Mesh* fish = myMeshManager->Create("fish", "fish.obj");
	Mesh* cube = myMeshManager->Create("cube", "cube.obj");

	//myObjectManager->CreateLight( // this also pushes to Object::Entities
	//	"lightObj",
	//	NULL,
	//	NULL,
	//	myShaderManager->DefaultShader,
	//	NULL,
	//	//myLightingManager->CreatePointLight(glm::vec3(0, 5, 0), glm::vec3(1, 1, 1), 1.0f)
	//);

	myObjectManager->Create( // this also pushes to Object::Entities
		"cubeObj",
		cube,
		wall,
		myShaderManager->DefaultShader,
		MyColliderManager->Create(cubeColl)
		
	);
	
	
	myObjectManager->Create( // this also pushes to Object::Entities
		"fishObj",
		fish,
		wall,
		myShaderManager->DefaultShader,
		MyColliderManager->Create(sphereColl)

	);
	//myObjectManager->CreateLight( // this also pushes to Object::Entities and LightObject::lightEntities
	//	"lightObj",
	//	cube,
	//	wall,
	//	myShaderManager->DefaultShader,
	//	NULL,
	//	myLightingManager->CreateData(myLightData)
	//);

	


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

		//myLightData->InitialiseLightData(myShaderManager->DefaultShader, myLightData);
		
		
		//if (Phys->TimeTicking)
		//{
		//	double currentFrame = glfwGetTime();
		//	deltatime = currentFrame - lastFrame;
		//	lastFrame = currentFrame;
		//	//Phys->Simulate(deltatime);
		//}
		
		
		for (auto& lObjs : LightObject::LightEntities)
		{
			//std::string number = sizeof(lObjs);
			myLightData->lightPos = lObjs->Position;
			myLightData->InitialiseLightData(myShaderManager->DefaultShader, myLightData);
			


		}
		myShaderManager->DefaultShader->UseShader();
		myLighting->Use(myCamera, myShaderManager->DefaultShader);
		//myLightData->InitialiseLightData(myShaderManager->DefaultShader, myLightData);
		//messageUI->RenderUI();
		//myLightData->InitialiseLightData(myCamera, myShaderManager->DefaultShader);
		
		
		
		for (auto& l : LightObject::LightEntities)
		{

		}
		 
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
		update_ui(myUI, myShaderManager, myObjectManager);

		//update camera
		update_camera(myCamera, myUI, window);
		

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







