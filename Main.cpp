

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include "shader.h"
#include "rotatingcamera.h"
#include "texturemanager.h"
#include "cube.h"
#include "model.h"
#include "utils.h"
#include "visualizer.h"
#include "connector.hpp"
#include "ExternalLibraries/ImGUI/imgui.h"
#include "ExternalLibraries/ImGUI/imgui_impl_opengl3.h"
#include "ExternalLibraries/ImGUI/imgui_impl_glfw.h"

float vertices[] = { -0.5f, -0.8f, 0.0f,
						1.0f, -0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f
};
Shader* defaultShader;
TextureManager texManager;
float lastFrame = 0.0f; // Time of last frame
bool firstMouse = true; 
float lastX, lastY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processKeyboardInput(GLFWwindow* window);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
GLFWwindow* initializeGLFWWindow();
RotatingCamera camera(glm::vec3(0.0f, 10.0f, 20.0f));

int main()
{
	GLFWwindow* window = initializeGLFWWindow();
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	if (window == NULL)
	{
		return -1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	char from[3] = "??";
	char to[3] = "??";

	Shader shader("lighting.vert", "lighting.frag");

	Scene scene(camera);
	Visualizer visualizer(scene);

	float previousTime = glfwGetTime();
	float deltaTimePrevious = glfwGetTime();
	int frameCount = 0;

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float currentTime = glfwGetTime();
		deltaTime = currentTime - deltaTimePrevious;
		deltaTimePrevious = currentTime;
		frameCount++;
		if (currentTime - previousTime >= 1.0f)
		{

			glfwSetWindowTitle(window, ((std::to_string(1000.0f / frameCount) + "ms to render").c_str()));
			frameCount = 0;
			previousTime += 1.0f;
		}

		// Input
		processKeyboardInput(window);
		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		visualizer.render();

		ImGui::Begin("Move piece");
		ImGui::InputText("From", from, sizeof(char) * 3);
		ImGui::InputText("To", to, sizeof(char) * 3);
		if (ImGui::Button("Move!"))
		{
			visualizer.makeMove(from, to);
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

GLFWwindow* initializeGLFWWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Checkers", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset, deltaTime);
}

void processKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);



	// Processing keyboard camera movement
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 


	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{ 
		camera.ProcessMouseMovement(xoffset, yoffset, deltaTime);
	}
}