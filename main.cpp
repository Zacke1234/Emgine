#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"'
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


#pragma once



int main()
{
	char* imageFile;
	
	
	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Emgine", NULL, NULL);

	
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
	
	

	Shader* myShader = new Shader("../Shader/VertexShader_1.glsl" ,"../Shader/FragmentShader_1.glsl");
	
	Camera* myCamera = new Camera();
	Texture* wallTex = new Texture("wall.jpg");
	Texture* myTexture = new Texture("Default 1.png");
	
	Lighting* myLighting = new Lighting();
	
	UI* myUI = new UI(window);
	ObjLoader* myObjLoader = new ObjLoader();
	MeshManager::Allocate();
	MeshManager* myMeshManager = &MeshManager::Get(); 
	
	Vertex myVertex{};
	

	Mesh mesh = myObjLoader->ObjParser("./teapot.obj"); //teapot.obj
	
	Cube* Cubemesh = myMeshManager->GetCube();
	Cube* ObjMesh = myMeshManager->GetObject();

	

	// Initialization 
	Cubemesh->InitializeCube();
	ObjMesh->InitializeObjectFile(&mesh);

	//auto loadMesh = myMeshManager->LoadCube();
	
	//auto object = new VirtualObject(&mesh, myTexture, myShader); // texture gets set here to the object though TODO: remove
	/*object->SetCube(*myCube);
	object->SetShader(*myShader);
	object->SetTexture(*myTexture);*/
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, myCamera->Mouse_Callback);

	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};

	/*object->Scale = glm::vec3(1, 1, 1);
	object->Position = glm::vec3(2, 2, 2);*/

	VirtualObject* myVirtualObject{};
	VirtualObject* VirtualObjectMesh{}; 
	std::string foo = "entity";
	
	
	VirtualObjectMesh = new VirtualObject(&mesh, myTexture, myShader, foo);

	VirtualObjectMesh->Position = glm::vec3(1, 1, 1);
	VirtualObjectMesh->Scale = glm::vec3(1, 1, 1);
	
	while (VirtualObject::Entities.size() < 3) 
	{

		myVirtualObject = new VirtualObject(&mesh, myTexture, myShader, foo);
		VirtualObject::Entities.push_back(myVirtualObject); 
		  
		
		myVirtualObject->Position = glm::vec3(rand() % 20, rand() % 20, rand() % 20);
		
		
	}  
	//myUI->virtobj = VirtualObject::Entities[0];
	
	//ObjMesh->InitialiseObjectFile(myObjLoader);
	VirtualObject::Entities.push_back(VirtualObjectMesh);
	
	//myLighting->Initialise();
	
	
	glEnable(GL_DEPTH_TEST);
	// loops until user closes window
	while (!glfwWindowShouldClose(window))
	{
		
		// Renders 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		// poll for and process events ?
		glfwPollEvents();

		

		myUI->RenderUI();
		
		myShader->UseShader();
		//myVirtualObject->SetMesh(mesh);
		//smyLighting->Use();
		for (auto& o : VirtualObject::Entities)
		{		
			//o->Draw(myCamera, myShader); // draws the cubes
			o->DrawObject(myCamera, myShader); // draws the mesh from the file. for example, the teapot mesh
			
			
		}

		//ObjMesh->DrawObject(myShader, VirtualObjectMesh); // Something has to up with the drawing, but I dont know what could be causing 		
		 
		
		myVirtualObject->Entities[VirtualObject::SelectedEntity]->Position = glm::vec3(myUI->xPos, myUI->yPos, myUI->zPos);
		myVirtualObject->Entities[VirtualObject::SelectedEntity]->Rotation = glm::vec3(myUI->xRot, myUI->yRot, myUI->zRot);
		myVirtualObject->Entities[VirtualObject::SelectedEntity]->Scale = glm::vec3(myUI->xScale, myUI->yScale, myUI->zScale);
		
		

		glm::mat4 Trans = glm::mat4(1);
		glm::mat4 View = glm::mat4(1);
		glm::mat4 Projection = glm::mat4(1);
		glm::vec3 Texture = glm::vec3(1);
		glm::vec2 TexCoords = glm::vec2(1);
		/*glm::vec3 vertex_Position = glm::vec3(1);
		glm::vec2 vertex_UV = glm::vec2(1);
		glm::vec3 vertex_Normal = glm::vec3(1);*/
		 

		myCamera->ProcessInput(window);
		

		//forces camera to lock into the window if your cursor goes back into the window
		//glfwSetCursorEnterCallback(window, myCamera->Cursor_enter_callback);
		//myGUI->Use();
	
		//myCube->Draw(myShader, objects);
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

	glfwTerminate();
	//std::cout << "hello engime" << std::endl;
	
	return 0;
}

