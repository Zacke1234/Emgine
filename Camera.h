#pragma once
#include <glm.hpp>
#include <string>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <glad.h>
#include <fstream>
#include <sstream>
#include <glfw3.h>

class Camera
{
public:
	static Camera* Instance;

	Camera();

	void CameraUpdate(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window);

	static void Mouse_Callback(GLFWwindow* window, double xpos, double ypos);

	void mouse_callback(double xpos, double ypos);
	
	static Camera* GetInstance();

	glm::mat4 myView;
	glm::mat4 projection;

	float cameraSpeed;

	float myWidth;
	float myHeight;

	float yaw = -90.0f;
	float pitch = 0;

	float fieldOfView = 70;

	static void Cursor_enter_callback(GLFWwindow* window, int entered);

	void cursor_enter_callback(GLFWwindow* window,int entered);

	

	bool TabbedIn = true;

	float deltatime = 0.0f;
	float lastFrame = 0.0f;

	glm::vec3 myPosition;
	

private:
	glm::vec3 myDirection;
	
	glm::vec3 myUp;
	glm::vec3 myRight;
	glm::vec3 myFront;
	
	
	glm::vec3 myTarget;
	
	
	//const float radius = 10.0f;
	unsigned int ShaderProgram;
	

	double curx;

	double cury;


};

