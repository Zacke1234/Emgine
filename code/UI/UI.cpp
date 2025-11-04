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
Lighting* light;
MeshManager* meshmang;
ObjectManager* objectMang;
ShaderManager* shaderMang;
ColliderManager* colliderMang;
TextureManager* textureMang;
LightingManager* lightMang;
LightData* newLightData;
ObjectType ObjType;
//const char* lightItems[255] = { "Directional", "Spot", "Spot" };

int lightEntityListing(UI* ui)
{
	// should I make an ID system for every obj?
	//objectMang->Find("");
	//&&Object::ObjectType objEnum = static_cast<Object::ObjectType>(Object::SelectedEntity);
	if (Object::SelectedEntity == LightObject::SelectedLightEntity)
	{
		//std::cout << "0";
	}
	for (int i = 0; i < Object::Entities.size(); i++)
	{
		
	}
	if (Object::Entities[Object::SelectedEntity, Object::Type_Light])
	{
		
	}

	
	/*if (objEnum == Object::Type_Light)
	{
		
	}*/
	// Cant I just use the objectType :light type??+
	
	// I want to be able to select the light entities and change their light type in the UI
	//if (Object::Entities[Object::Type_Light])
	//{
	//	std::cout << "light object selected" << std::endl;
	//}
	// If selected entity is light type then blah blah blah
	if (Object::Entities[Object::SelectedEntity] == Object::Entities[Object::SelectedEntity, Object::ObjectType::Type_Light])
	{
		 // it does that because enums are a type of int..
	}
	
	//switch (objEnum)
	//{
	//case Object::Type_NULL:
	//	break;
	//case Object::Type_Light:
	//	std::cout << "obj enum";
	//	break;
	//case Object::Type_Mesh:
	//	break;
	//case Object::Type_Cube:
	//	break;
	//default:
	//	break;
	////}
	//for (int i = 0; i < Object::Entities.size(); i++)
	//{
	//	int b = Object::SelectedEntity;
	//	printf(R"(%d )", b);
	//	//LightObject::SelectedLightEntity = i;
	//	
	//}
	
	return 0;
}

int uiObjectList(UI* ui) 
{
	
	
	for (int i = 0; i < Object::Entities.size(); i++)
	{
		ImGui::PushID(i);
		if (ImGui::Button(Object::Entities[i]->namn.c_str()))
		{
			
			Object::SelectedEntity = i;
			Object::SelectedEntityVec[i];
			//if (Object::SelectedEntity == LightObject::SelectedLightEntity) // &&? How do I check if the selected entity is the same as the selected light entity, Cause I want to know when the user is selecting the Light object
			//{
			//	std::cout << "light object selected" << std::endl;
			//}
			//if (Object::SelectedEntity == )
			printf(R"(%d )", Object::SelectedEntity);
			//std::cout << "Is kinematic?" << Object::&myCollider
			ui->xPos = Object::Entities[i]->Position[0];
			ui->yPos = Object::Entities[i]->Position[1];
			ui->zPos = Object::Entities[i]->Position[2];

			ui->xRot = glm::degrees(Object::Entities[i]->Rotation[0]);
			ui->yRot = glm::degrees(Object::Entities[i]->Rotation[1]);
			ui->zRot = glm::degrees(Object::Entities[i]->Rotation[2]);

			ui->xScale = Object::Entities[i]->Scale[0];
			ui->yScale = Object::Entities[i]->Scale[1];
			ui->zScale = Object::Entities[i]->Scale[2];

			//ui->SetLightType = Object::Entities[i]->ObjType;
			ui->SetLightType = Object::Entities[i]->ObjType;
			
			
			//virtobj->Scale = cubeCollider->scale; cubeCollider is nullptr
		}
		//Object::Entities[0] = o;
		ImGui::PopID();
	}
	return 0;
}


int classes() {
	glm::vec3 extents = { 1,1, 1 };
	glm::vec3 extentsPlane = { 7 / 2, 0.5f / 2, 7 / 2 };
	glm::vec3 center = { 0, 0,0 }; float radius = 0.5f; glm::vec3 pos = { 0,0,0 };
	glm::vec3 scale = { 1,1,1 };
	
	cubeColl2 = new CubeCollider(center, extents, pos);
	newLightData = new LightData();
	shaderMang = new ShaderManager();
	colliderMang = new ColliderManager();
	textureMang = new TextureManager();
	meshmang = new MeshManager();
	lightMang = new LightingManager();
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
	
	
	classes();
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
	std::string cubeName = "Cube";
	// Implement a Camera class and UI to configure it for rendering your scene
	lightEntityListing(this);
	lightEntityListing(this);

	if (ImGui::Button("Create new mesh"))
	{
		if (nameBuffer[0] == '\0' && nameBuffer != NULL)
		{
			objectmanager->Create(
				"Mesh", // Name
				meshmang->Create(nameBuffer, meshBuffer),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				colliderMang->Create(cubeColl2)
			);
		}
		else
		{
			objectmanager->Create(
				nameBuffer, // Name
				meshmang->Create(nameBuffer, meshBuffer),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				colliderMang->Create(cubeColl2)
			);
		}


		//Object::Entities.push_back(objectMang->ObjectMesh);

		



	}
	//std::string test = nameBuffer;
	if (ImGui::Button("Create new cube"))
	{
		if (nameBuffer[0] == '\0' && nameBuffer != NULL)
		{
			std::cout << "name field is empty" << std::endl;
			//name[254] = 'cube';
			objectmanager->Create("Cube",
				meshmang->Create("cube", "cube.obj"),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				colliderMang->Create(cubeColl2)
			);
		}
		else
		{
			objectmanager->Create(nameBuffer,
				meshmang->Create("cube", "cube.obj"),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				colliderMang->Create(cubeColl2)
			);
		}





		

	}

	if (ImGui::Button("Create new light"))
	{

		if (nameBuffer[0] == '\0' && nameBuffer != NULL)
		{
			objectmanager->CreateLight("Light",
				meshmang->Create("cube", "cube.obj"),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				NULL,
				newLightData
			);
			
		}
		else {
			objectmanager->CreateLight(nameBuffer,
				meshmang->Create("cube", "cube.obj"),
				textureMang->Create(std::string(nameBuffer + tex), textureBuffer),
				shader->DefaultShader,
				NULL,
				newLightData
			);
			
		}


		//newLightData->SetPoint();

		
		//newLightData->InitialiseLightData(shader->DefaultShader, newLightData);


		//const char* Items[]{ "Directional", "Point", "Spot"};
	}
	
	if (ImGui::Combo("Light type", &SelectedItem, Items, IM_ARRAYSIZE(Items)))
	{
		// How do I check if the selected entity is the same as the selected light entity, Cause I want to know when the user is selecting the Light object
		if (SelectedItem == 0)
		{
			//SetLightType = 1;
			std::cout << "directional" << std::endl;
			//Object::Entities[0]->LightData::LightVar;
			/*if (Object::Entities[Object::SelectedEntity] == LightObject::Entities[LightObject::SelectedLightEntity])
			{
				Object::Entities[Object::SelectedEntity]->SetTexture(*texture);
			}*/
			/*if (LightObject::LightEntities)
			{
				LightObject::LightEntities[LightObject::SelectedLightEntity]->SetDirectional(newLightData);
				
			}*/
			
		}
		if (SelectedItem == 1 && SetLightType == 1)
		{
			SetLightType = 2;
			std::cout << "point" << std::endl;
			/*if (Object::Entities[Object::Type_Light])
			{
				std::cout << "light object selected" << std::endl;
			}
			std::cout << "point" << std::endl;*/
		}
		if (SelectedItem == 2 && SetLightType == 1)
		{
			
			if (Object::SelectedEntityVec[Object::Type_Light])
			{
				std::cout << "spot" << std::endl;
			};
			//LightObject::LightEntities[LightObject::SelectedLightEntity]->SetDirectional(newLightData);
			
		}
	};
	
	ImGui::Text("");
	

   //ImGui::Text("IsKinematic", &check);
	if (ImGui::Checkbox("Is kinematic", &check)) // a bit jank
	{
		//Object::Entities[Object::SelectedEntity]->myCollider->isKinematic = check;
		//virtobj->Entities[Object::SelectedEntity]->myCollider->isKinematic;
	}

	if (ImGui::Button("Change Texture"))
	{
		texture = new Texture(textureBuffer);
		Object::Entities[Object::SelectedEntity]->SetTexture(*texture);
	}

	if (ImGui::Button("Change name"))
	{
		Object::Entities[Object::SelectedEntity]->SetName(nameBuffer);
	}


	if (ImGui::Button("Play"))
	{

	}

	ImGui::Text("Mesh Manager");
	//int n = sizeof(virtobj->Entities);

	
	

	uiObjectList(this);

	
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
		