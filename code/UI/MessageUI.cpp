#include "MessageUI.h"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
MessageUI::MessageUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	//ImGui::GetCurrentContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	
	ImGui_ImplOpenGL3_Init("#version 330");
	//io.ConfigFlags |= ImGuiConfigFLags_ViewportsEnable;


};

ImVec2 messageWindowPos = ImVec2(100, 100);

void MessageUI::RenderUI()
{
	
	/*ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();  
	
	ImGui::Render();
	ImGui::SetWindowPos(messageWindowPos);
	ImGui::NewFrame();
	ImGui::Begin("Messager");*/ //crashes the engine
	
	ImGui::Text("Message");
}
