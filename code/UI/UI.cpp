#include "UI.h"
#include "Object.h"
#include "vector"
#include "imgui.h"
#include "Shader.h"
#include "Texture.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>
#pragma once

CubeCollider* cubeColl2;
MeshManager* meshmang;
ObjectManager* objectMang;
ShaderManager* shaderMang;
ColliderManager* colliderMang;
TextureManager* textureMang;

int init_colliders2() {
	glm::vec3 extents = { 1,1, 1 };
	glm::vec3 extentsPlane = { 7 / 2, 0.5f / 2, 7 / 2 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };

	cubeColl2 = new CubeCollider(center, extents, pos);
	shaderMang = new ShaderManager();
	colliderMang = new ColliderManager();
	textureMang = new TextureManager();
	meshmang = new MeshManager();
	return 0;
}

UI::UI(GLFWwindow* window) // unitilized
{
	
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	/*io.ConfigFlags |= ImGuiViewportFlags_None;
	io.ConfigFlags |= ImGuiConfigFlags_None;
	
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}*/
	
	//camera = new Camera();
	ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true); // changing this to false makes the hover over highlight effect work on the button, but I still
	// can't interact with it, nvm fixed all of this now
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	
	
	init_colliders2();
}

void UI::RenderUI(ShaderManager* shader, ObjectManager* objectmanager)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::NewFrame();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Begin("Emgine Properties");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	//ImGui::ShowDemoWindow();
	ImGui::Text("");

	if (ImGui::Button("echo"))
	{
		std::cout << "echo" << "\n";
		//std::cout << textureFile << "\n";
		/*for (int i = 0; i < Object::Entities.size(); i++)
		{
			std::cout << Object::Entities[i] << " ";
		}*/
	}
	ImGui::Text("Type in the exact file name");

	textureFile = ImGui::InputText("texture file", textureBuffer, sizeof(textureBuffer) - 1);  // does not work as intended
	name = ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer) - 1);
	charMesh = ImGui::InputText("Mesh", meshBuffer, sizeof(meshBuffer) - 1); // not yet implemented

	ImGui::InputFloat("Field of view", &fov, 1.0f, 1.0f, "%.2f");

	ImGui::InputFloat("Camera sensitivity", &sens, 0.1f, 1.0f, "%.2f");

	std::string tex = "_tex";
	//ImGui::Text("Change camera speed");
	//ImGui::InputFloat("Camera speed", &speed, 1.0f, 1.0f, "%.1f"); // supposed to change speed of camera cause

	// Implement a Camera class and UI to configure it for rendering your scene

	if (ImGui::Button("Create new mesh"))
	{
			
		
		objectmanager->Create(
			nameBuffer, // Name
			meshmang->Create(nameBuffer, meshBuffer),
			textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
			shader->DefaultShader,
			colliderMang->Create(cubeColl2)
		);

		//Object::Entities.push_back(objectMang->ObjectMesh);
		
		type = ObjectType::Type_Mesh;
		
		
		
	}

	if (ImGui::Button("Create new cube"))
	{
		
		objectmanager->Create(nameBuffer,
			meshmang->Create("cube", "cube.obj"),
			textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
			shader->DefaultShader,
			colliderMang->Create(cubeColl2)
		);
		type = ObjectType::Type_Cube;

	}
	// cubeCollider->isKinematic;

   //ImGui::Text("IsKinematic", &check);
	if (ImGui::Checkbox("Is kinematic", &check)) // a bit jank
	{
		//Object::Entities[Object::SelectedEntity]->myCollider->isKinematic = check;
		//virtobj->Entities[Object::SelectedEntity]->myCollider->isKinematic;
	}

	if (ImGui::Button("Change Texture"))
	{
		textureMang->Find(std::string(nameBuffer + tex));

		 
	}

	if (ImGui::Button("Change name"))
	{
	}

	if (ImGui::Button("Play"))
	{

	}

	ImGui::Text("Mesh Manager");
	//int n = sizeof(virtobj->Entities);
	

	float value = 0;

	for (int i = 0; i < Object::Entities.size(); i++)
	{
		ImGui::PushID(i);
		if (ImGui::Button(Object::Entities[i]->namn.c_str()))
		{

			Object::SelectedEntity = i;
			printf(R"(%d )", Object::SelectedEntity);
			//std::cout << "Is kinematic?" << Object::&myCollider
			xPos = Object::Entities[i]->Position[0];
			yPos = Object::Entities[i]->Position[1];
			zPos = Object::Entities[i]->Position[2];

			xRot = glm::degrees(Object::Entities[i]->Rotation[0]);
			yRot = glm::degrees(Object::Entities[i]->Rotation[1]);
			zRot = glm::degrees(Object::Entities[i]->Rotation[2]);

			xScale = Object::Entities[i]->Scale[0];
			yScale = Object::Entities[i]->Scale[1];
			zScale = Object::Entities[i]->Scale[2];
			//virtobj->Scale = cubeCollider->scale; cubeCollider is nullptr
		}
		//Object::Entities[0] = o;
		ImGui::PopID();
	}
	//ImGui::InputText("texture file", buf, sizeof(buf) - 1);

	ImGui::Text("");

	ImGui::InputFloat("X pos", &xPos, step, step_fast);
	ImGui::InputFloat("Y pos", &yPos, step, step_fast);
	ImGui::InputFloat("Z pos", &zPos, step, step_fast);
	ImGui::Text("");
	ImGui::InputFloat("X rotate", &xRot, step, step_fast);
	ImGui::InputFloat("Y rotate", &yRot, step, step_fast);
	ImGui::InputFloat("Z rotate", &zRot, step, step_fast);
	ImGui::Text("");
	ImGui::InputFloat("X scale", &xScale, step, step_fast);
	ImGui::InputFloat("Y scale", &yScale, step, step_fast);
	ImGui::InputFloat("Z scale", &zScale, step, step_fast);
	
	//ImGui_ImplGlfw_Shutdown();
	ImGui::End();
	ImGui::EndFrame();; 
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//glfwSwapBuffers(window);
	glfwPollEvents();
}
