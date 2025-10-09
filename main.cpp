#include <stdio.h>
#include "imgui.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Lighting.h"
#include "string"
#include <cstdlib>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Object.h"
#include "UI.h"
#include "MeshManager.h"
#include "ObjLoader.h"
#include "Physics.h"
#include "Memory.h"
#include "Collider.h"
#include "Message.h"
#include "Threading.h"
#include "Observer.h"
#include <float.h>
#include <thread>
#include <mutex>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



using namespace std;
#pragma once




int update_camera(Camera* cam, UI* myUI, GLFWwindow* window)
{
	cam->ProcessInput(window);
	cam->CameraUpdate(window);
	cam->fieldOfView = myUI->fov;
	cam->sensitivity = myUI->sens;
	return 0;
}
int update_ui(UI* myUI, Shader* myShader)
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
int update_meshes(Cube* cubeMesh, Mesh* myMesh, CubeCollider* cubeColl) {
	
	
	return 0;
}

 

int main()
{
	
	
	
	
	
	if (!glfwInit())
	{
		
		std::cout << "Failed to initialize glfw" << endl;
		//myMessage->SendMessage(message, 0);
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
		//message = "Failed to initialize GLAD";
		std::cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	
	int megaBytes = 0;

	
	
	//myMemory->T1();
	//thread thread1;
	Threading* myThread = new Thread(); 
	/*std::thread t1(myThread);
	t1.join();*/
	//Threading::thread1(myThread->DoWork);
	
	/*std::thread t1(test);
	
	std::thread t2(test);
	t1.join();
	t2.join();
	std::cout << number;*/
	
	//MessageUI* messageUI = new MessageUI(window);


	//init shader/lighting
	Shader* myShader = new Shader("../Shader/VertexShader_1.glsl" ,"../Shader/FragmentShader_1.glsl");
	Lighting* myLighting = new Lighting();
	
	//init camera
	Camera* myCamera = new Camera();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, myCamera->Mouse_Callback);

	//loading Textures
	Texture* wallTex = new Texture("wall.jpg");
	Texture* myTexture = new Texture("Default 1.png");
	//load_textures();
	

	//init meshmanager
	MeshManager::Allocate();
	MeshManager* myMeshManager = &MeshManager::Get(); // the mesh manager, it also caches my meshes.

	/*Message* myMessage;
	string test = "test";
	myMessage->Notify();*/
	
	
	ObjLoader* myObjLoader = new ObjLoader();
	
	UI* myUI = new UI(window);

	//Thread thread;
	//thread1.join();

	//myThread = &thread   ;


	Physics* Phys = new Physics();

	Observer* Observe = new Observer();
	Subject* subject = new Subject();
	
	Output output;
	subject->Attach(Observe);
	string message = "Test";
	/*Observe->Update(message);
	subject->Notify();*/


	
	
	
	
	

	glm::vec3 extents = { myUI->xScale / 2, myUI->yScale / 2, myUI->zScale / 2};
	glm::vec3 extentsPlane = { 7 / 2, 0.5f / 2, 7 / 2};
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	Collider* collider = new Collider();
	CubeCollider* cubeColl = new CubeCollider(center, extents, pos);
	CubeCollider* planeColl = new CubeCollider(center, extentsPlane, pos);

	Cube* Cubemesh = myMeshManager->LoadCube();
	
	Mesh* MeshMesh = myMeshManager->LoadMesh("out.bin"); // cacheing happens here when it also loads the meshes in.
	// teapot mesh looks weird at the handle				

	Object* ObjectMesh{};
	Object* CubeObject{};
	Object* PlaneObject{};
	
	BinaryFile bin("out.bin");
	//bin.ReadFile();
	//bin.WriteFile();

	ofstream write("out.bin", std::ios::binary); // ./out.bin
	ifstream read("fish.obj");

	myObjLoader->ReadFromBinary(read);
	myObjLoader->WriteToBinary(write);
	
	write.close();
	read.close();
	
	string name = "Mesh";
	string name2 = "Cube";
	string name3 = "Plane";

	CubeObject = new Object(Cubemesh, myTexture, myShader, name2, cubeColl);
	PlaneObject = new Object(Cubemesh, myTexture, myShader, name3, planeColl);

	//update_meshes();

	PlaneObject->myCollider->isKinematic = true;
	PlaneObject->Scale = glm::vec3(7, 0.5f, 7);
	PlaneObject->Position = glm::vec3(0, 0, 0);

	Object::Entities.push_back(CubeObject);
	Object::Entities.push_back(PlaneObject);

	
	while (Object::Entities.size() < 5) 
	{
		SphereCollider* sphereColl = new SphereCollider(center, radius, pos);
		ObjectMesh = new Object(MeshMesh, myTexture, myShader, name, sphereColl);
		
		
		Object::Entities.push_back(ObjectMesh);
		
		ObjectMesh->myCollider->isKinematic = false;
		
		ObjectMesh->Position = glm::vec3(rand() % 5, 10, rand() % 5);
		
	}  
	
	float deltatime = 0.0f;
	float lastFrame = 0.0f;
	unsigned int depthMapFBO = 0;
	unsigned int depthMap = 0;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	//ConcreteMessage* message = new ConcreteMessage(myMeshManager->c1, myObjLoader->c2);

	myCamera->myPosition = glm::vec3(0, 3, 0);

	
	//ConcreteMessage* message = new ConcreteMessage(myObjLoader->c1, myMeshManager->c2);

	Memory* myMemory = new Memory();
	myMemory->HasMemoryAvailable(megaBytes);
	/*thread t1(myObjLoader);
	thread t2(Phys);*/

	/*t1.join();
	t2.join();*/
	

	glEnable(GL_DEPTH_TEST);
	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

		
		//myThread->DoWork(deltatime);
		
		// poll for and process events ?
		glfwPollEvents();

		myMemory->LoadInMemory(myShader, Cubemesh, myCamera, myLighting, CubeObject, myUI, myMeshManager, MeshMesh, collider);

		
		
		
		if (Phys->TimeTicking)
		{
			double currentFrame = glfwGetTime();
			deltatime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			Phys->Simulate(deltatime);
		}
		
		

		myShader->UseShader();
		
		
		//messageUI->RenderUI();

		
		
		myLighting->Use(myCamera, myShader);

		
		//Drawcall objects
		for (auto& o : Object::Entities)
		{
			
			o->Draw(myCamera, myShader); // draws the cubes
			
		}


		// render UI (after/ON TOP OF drawcall)
		update_ui(myUI, myShader);

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
	myMemory->ClearMemory(myShader, Cubemesh, myCamera, myLighting, CubeObject, myUI, myMeshManager, MeshMesh, collider);
	//delete myMemory;
	glfwTerminate();
	//std::cout << "hello engime" << std::endl;
	
	/*delete myShader;*/
	return 0;
}

