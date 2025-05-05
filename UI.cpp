#include "VirtualObject.h"
#include "MeshManager.h"
#include "vector"
#include "imgui.h"
#include "UI.h"
#include "Shader.h"
#include "Texture.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>


UI::UI(GLFWwindow* window) // unitilized
{
	
	isCube = false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//camera = new Camera();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true); // changing this to false makes the hover over highlight effect work on the button, but I still
	// can't interact with it, nvm fixed all of this now
	ImGui_ImplOpenGL3_Init("#version 330");
	
}

void UI::RenderUI(Shader* shader)
{
	glm::vec3 extents = { 1,1,1 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };
	SphereCollider* sphereColl = new SphereCollider(center, radius, pos);
	CubeCollider* cubeColl = new CubeCollider(center, extents, pos);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::Begin("Emgine Properties");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	//ImGui::ShowDemoWindow();
	ImGui::Text("");

	if (ImGui::Button("echo"))
	{
		std::cout << "echo" << "\n";
		//std::cout << textureFile << "\n";
		/*for (int i = 0; i < VirtualObject::Entities.size(); i++)
		{
			std::cout << VirtualObject::Entities[i] << " ";
		}*/
	}
	ImGui::Text("Type in the exact file name");

	textureFile = ImGui::InputText("texture file", buf, sizeof(buf) - 1);  // does not work as intended
	name = ImGui::InputText("Name", buf2, sizeof(buf2) - 1);
	charMesh = ImGui::InputText("Mesh", buf_Mesh, sizeof(buf_Mesh) - 1); // not yet implemented
	
	ImGui::InputFloat("Field of view", &fov, 1.0f, 1.0f, "%.2f");

	ImGui::InputFloat("Camera sensitivity", &sens, 0.1f, 1.0f, "%.2f");


	//ImGui::Text("Change camera speed");
	//ImGui::InputFloat("Camera speed", &speed, 1.0f, 1.0f, "%.1f"); // supposed to change speed of camera cause
	
	// Implement a Camera class and UI to configure it for rendering your scene

	if (ImGui::Button("Create new mesh"))
	{
		VirtualObject* meshObj = new VirtualObject();
		
		texture = new Texture(buf);
		newCollider = new Collider();
		/*meshmang = new MeshManager();
		mesh = new Mesh();*/
		

		
		
		if (textureFile == '\0')
		{
			texture = new Texture("Default 1.png");
		}
		
		meshObj->SetTexture(*texture);
		//mesh = meshmang->LoadMesh("fish.obj");
		mesh = MeshManager::Get().LoadMesh("./fish.obj");
		if (mesh != nullptr)
		{
			
			meshObj->SetMesh(*mesh);
		}
		
		//meshObj->CreateMesh();

		meshObj->Position = glm::vec3(1, 1, 1);
		meshObj->Scale = glm::vec3(1, 1, 1);
		meshObj->SetShader(*shader);
		meshObj->SetName(buf2);

		meshObj->myCollider = newCollider;
		newCollider->isKinematic = true;

		if (name == '\0')
		{
			meshObj->SetName("Mesh");
		}
		VirtualObject::Entities.push_back(meshObj);
	}

	if (ImGui::Button("Create new cube")) 
	{
		glm::vec3 center = { 0, 0,0 };
		glm::vec3 extents = { 0,0,0 };
		//mesh = new Mesh();
		VirtualObject* CubeObj = new VirtualObject();
		texture = new Texture(buf);	
		newCollider = new Collider();
	
		CubeObj->IsCube = true;
		CubeObj->IsMesh = false;
		if (textureFile == '\0') 
		{
			texture = new Texture("Default 1.png");
		}
		
		
		CubeObj->SetTexture(*texture);
		
		CubeObj->SetCube(*MeshManager::Get().LoadCube());
		CubeObj->Position = glm::vec3(1, 1, 1);
		CubeObj->Scale = glm::vec3(1, 1, 1);
		CubeObj->SetShader(*shader);
		
		CubeObj->SetName(buf2);
		
		CubeObj->myCollider = newCollider;
		newCollider->isKinematic = true;
		
		if (name == '\0')
		{
			CubeObj->SetName("Cube");
		}
		VirtualObject::Entities.push_back(CubeObj);
		
	}
	 // cubeCollider->isKinematic;
	
	//ImGui::Text("IsKinematic", &check);
	if (ImGui::Checkbox("Is kinematic", &check)) // a bit jank
	{
		VirtualObject::Entities[VirtualObject::SelectedEntity]->myCollider->isKinematic = check;
		//virtobj->Entities[VirtualObject::SelectedEntity]->myCollider->isKinematic;
	}

	if (ImGui::Button("Change Texture"))
	{
		texture = new Texture(buf);

		VirtualObject::Entities[VirtualObject::SelectedEntity]->SetTexture(*texture);
	}
	   
	if (ImGui::Button("Change name"))
	{
		VirtualObject::Entities[VirtualObject::SelectedEntity]->SetName(buf2);
	}

	if (ImGui::Button("Play"))
	{
		
	}
	
	ImGui::Text("Mesh Manager");
	int n = sizeof(virtobj->Entities);

	

	float value = 0;

	for (int i = 0; i < VirtualObject::Entities.size(); i++)
	{
		ImGui::PushID(i);
		if (ImGui::Button(VirtualObject::Entities[i]->namn.c_str()))
		{
			
			VirtualObject::SelectedEntity = i;
			printf(R"(%d )", VirtualObject::SelectedEntity);
			xPos = VirtualObject::Entities[i]->Position[0];
			yPos = VirtualObject::Entities[i]->Position[1];
			zPos = VirtualObject::Entities[i]->Position[2];

			xRot = glm::degrees(VirtualObject::Entities[i]->Rotation[0]);
			yRot = glm::degrees(VirtualObject::Entities[i]->Rotation[1]);
			zRot = glm::degrees(VirtualObject::Entities[i]->Rotation[2]);

			xScale = VirtualObject::Entities[i]->Scale[0];
			yScale = VirtualObject::Entities[i]->Scale[1];
			zScale = VirtualObject::Entities[i]->Scale[2];
			//virtobj->Scale = cubeCollider->scale; cubeCollider is nullptr
		}
		//VirtualObject::Entities[0] = o;
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
	
}
