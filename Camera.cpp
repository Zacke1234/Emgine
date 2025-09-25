#include "Camera.h"
#include "imgui.h"
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <glad.h>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"




glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
float lastX = 400, lastY = 300;
Camera* Camera::Instance;
int Entered;


//Shader* myShader = new Shader("../Shader/VertexShader_1.glsl", "../Shader/FragmentShader_1.glsl");

Camera::Camera()
{

	
	myTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	
	myDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	myPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	myFront = glm::vec3(1.0f, 0.0f, 0.0f);
	myUp = glm::vec3(0.0f, -1.0f, 0.0f);
	
	myWidth = 800.0f;
	myHeight = 600.0f;
	
	myView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	curx = 0;
	cury = 0;

	cameraSpeed = 3.0f * deltatime;
}

void Camera::CameraUpdate(GLFWwindow* window) // the mouse cursor is still not good, when you tab in, it will just snap to another position again, need to fix
{
	
	if (!TabbedIn)
	{
		return;
	}
	myUp = glm::cross(myDirection, myRight);
	
	double currentFrame = glfwGetTime();
	deltatime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	projection = glm::perspective(glm::radians(fieldOfView), myWidth / myHeight, 0.1f, 200.0f);

	myRight = glm::normalize(glm::cross(WorldUp, myDirection));
	myUp = glm::cross(myDirection, myRight);
	myView = glm::lookAt(myPosition, myPosition + myDirection, myUp);

	mouse_callback(lastX, lastY);

}

void Camera::ProcessInput(GLFWwindow* window)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		myPosition += cameraSpeed * myDirection;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		myPosition -= cameraSpeed * myDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		
		myPosition -= glm::normalize(glm::cross(myDirection, myUp)) * cameraSpeed;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		myPosition += glm::normalize(glm::cross(myDirection, myUp)) * cameraSpeed;
		
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		TabbedIn = false;
		
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		TabbedIn = true;
		//io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
		
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//std::cout << "shift" << "\n";
		cameraSpeed = 9.0f * deltatime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		//std::cout << "let go of shift" << "\n";
		cameraSpeed = 3.0f * deltatime;
	}
	
}

void Camera::Mouse_Callback(GLFWwindow* window, double xpos, double ypos)
{
 	ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos); //this was the fix to the mouse input not working with the imgui
	lastX = xpos;
	lastY = ypos;
}




void Camera::mouse_callback(double xpos, double ypos)
{
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (!TabbedIn)
	{
		return;
	}

	bool firstMouse = true;
	

	//std::cout << xpos << "\n";
	if (firstMouse)
	{
		/*lastX = xpos;
		lastY = ypos;
		firstMouse = false;*/
	}

	float xoffset = xpos - curx;
	float yoffset = cury - ypos;
	curx = xpos;
	cury = ypos;

	//sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0)
	{
		pitch = -89.0f;
	}

	
	glm::vec3 direction = glm::vec3(0, 0, 0);
	
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	myDirection = glm::normalize(direction);
	//myCamera->myView = glm::lookAt(direction, direction, myCamera->myFront, myCamera->myUp);
	//myView = glm::lookAt(myPosition, myPosition + myFront, myUp);
	/*myCamera->myRight = glm::normalize(glm::cross(direction, WorldUp));
	myCamera->myUp = glm::normalize(glm::cross(myCamera->myRight, direction));*/


	
}

Camera* Camera::GetInstance()
{
	if (Camera::Instance == nullptr)
	{
		Camera::Instance = new Camera();
	}
	return Camera::Instance;
}



//void Camera::Cursor_enter_callback(GLFWwindow* window, int entered)
//{
//	//cursor_enter_callback(window, entered);
//	Entered = entered;
//}
//
//void Camera::cursor_enter_callback(GLFWwindow* window,int entered)
//{
//	
//	if (entered)
//	{
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//		//mouseOutsideWindow = false;
//	}
//	else
//	{
//		//mouseOutsideWindow = true;
//	}
//}


