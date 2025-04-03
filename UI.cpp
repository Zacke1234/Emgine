#include "VirtualObject.h"
#include "MeshManager.h"
#include "vector"
#include "imgui.h"
#include "UI.h"
#include "Cube.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <iostream>


UI::UI(GLFWwindow* window)
{
	shade = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	isCube = false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	camera = new Camera();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true); // changing this to false makes the hover over highlight effect work on the button, but I still
	// can't interact with it, nvm fixed all of this now
	ImGui_ImplOpenGL3_Init("#version 330");
	
}

void UI::RenderUI(/*std::vector<VirtualObject*> object, GLFWwindow* window*/)
{
	
	
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

	textureFile = ImGui::InputText("texture file", buf, sizeof(buf) - 1);  
	name = ImGui::InputText("Name", buf2, sizeof(buf2) - 1);

	ImGui::Text("Change camera speed");
	camera->cameraSpeed = ImGui::InputText("Default speed is 3", buf3, sizeof(buf3) - 1); // supposed to change speed of camera cause
	// Implement a Camera class and UI to configure it for rendering your scene



	if (ImGui::Button("Create new cube")) 
	{
		glm::vec3 center = { 0, 0,0 };
		glm::vec3 extents = { 0,0,0 };
		//mesh = new Mesh();
		virtobj = new VirtualObject();
		texture = new Texture(buf);	
		newCollider = new Collider();

		virtobj->IsCube = true;
		virtobj->IsMesh = false;
		if (textureFile == '\0') 
		{
			texture = new Texture("Default 1.png");
		}
		
		
		virtobj->SetTexture(*texture);
		
		virtobj->SetCube(*MeshManager::Get().GetCube()); 
		virtobj->Position = glm::vec3(1, 1, 1);
		virtobj->Scale = glm::vec3(1, 1, 1);
		virtobj->SetShader(*shade);
		//virtobj->SetMesh(*mesh); 
		virtobj->SetName(buf2);
		
		virtobj->myCollider = newCollider;
		newCollider->isKinematic = true;
		
		if (name == '\0')
		{
			virtobj->SetName("Cube");
		}
		VirtualObject::Entities.push_back(virtobj);
		
	}
	 // cubeCollider->isKinematic;
	
	//ImGui::Text("IsKinematic", &check);
	if (ImGui::Checkbox("Is kinematic", &check)) // a bit jank
	{
		virtobj->Entities[VirtualObject::SelectedEntity]->myCollider->isKinematic = check;
		//virtobj->Entities[VirtualObject::SelectedEntity]->myCollider->isKinematic;
	}

	if (ImGui::Button("Change Texture"))
	{
		texture = new Texture(buf);
		virtobj = new VirtualObject();

		virtobj->Entities[VirtualObject::SelectedEntity]->SetTexture(*texture);
	}
	   
	if (ImGui::Button("Change name"))
	{
		virtobj = new VirtualObject();
		virtobj->Entities[VirtualObject::SelectedEntity]->SetName(buf2);
	}
	

	int n = sizeof(virtobj->Entities);

	int idx;

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

			xRot = VirtualObject::Entities[i]->Rotation[0];
			yRot = VirtualObject::Entities[i]->Rotation[1];
			zRot = VirtualObject::Entities[i]->Rotation[2];

			xScale = VirtualObject::Entities[i]->Scale[0];
			yScale = VirtualObject::Entities[i]->Scale[1];
			zScale = VirtualObject::Entities[i]->Scale[2];

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
