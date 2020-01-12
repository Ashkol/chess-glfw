

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include "shader.h"
#include "camera.h"
#include "texturemanager.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
float vertices[] = { -0.5f, -0.8f, 0.0f,
						1.0f, -0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f
};
Shader* defaultShader;
TextureManager texManager;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* initializeGLFWWindow();
Camera* camera;

int main()
{
	GLFWwindow* window = initializeGLFWWindow();
	if (window == NULL)
	{
		return -1;
	}
	unsigned int texID = texManager.loadTexture("Assets/Textures/container.png");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);

	defaultShader = new Shader("vertex.vert", "fragment.frag");

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);
		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		defaultShader->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

GLFWwindow* initializeGLFWWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Checkers", NULL, NULL);
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}