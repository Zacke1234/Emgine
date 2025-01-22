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
	isCube = false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true); // changing this to false makes the hover over highlight effect work on the button, but I still
	// can't interact with it, nvm fixed all of this now
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::RenderUI(/*std::vector<VirtualObject*> object, GLFWwindow* window*/)
{
	shade = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");
	
	//Camera* cam = new Camera();
	// 
	//Cube* myCube = new Cube();
	//objects.push_back(myVirtualObject);
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

	//int b;
	//ImGui::InputInt("label", &virtobj->SelectedEntity, step2, step2_fast);

	if (ImGui::Button("Create new cube")) // this just dosen't make a cube anymore, gives an error instead, probably cause of the cube/mesh code change, no longer gives an error
	{
		mesh = new Mesh();
		isCube = true;
		virtobj = new VirtualObject();
		//virtobj->isCube = true;
		texture = new Texture(buf);	// won't work if I press "create new cube" while the input field is empty, if I were to fill it then it still won't work.
		// it seems to only work if I input the file then click "create new cube" EDIT: now it dosen't work at all,

		if (buf == "") // if the field is empty it should make the cube have the default texture by default, but that dosen't work for some reason.
		{
			texture = new Texture("Default 1.png");
		}
		// \0
		VirtualObject::Entities.push_back(virtobj);

		//virtobj->Draw(cam, shade);
		 
		
		virtobj->SetTexture(*texture);
		virtobj->SetCube(*MeshManager::Get().GetCube()); 
		virtobj->Position = glm::vec3(1, 1, 1);
		virtobj->Scale = glm::vec3(1, 1, 1);
		virtobj->SetShader(*shade);
		virtobj->SetMesh(*mesh); // the mesh is set here, it no longer gives an error, but it can't render into the engine
		

		//virtobj->SelectedEntity = 3;
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
	name = ImGui::InputText("Name", buf2, sizeof(buf2) - 1);

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
