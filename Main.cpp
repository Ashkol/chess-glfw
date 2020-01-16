

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

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
float vertices[] = { -0.5f, -0.8f, 0.0f,
						1.0f, -0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
						-0.5f, 0.5f, 0.0f
};
Shader* defaultShader;
TextureManager texManager;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void initializeCamera();
GLFWwindow* initializeGLFWWindow();
RotatingCamera camera(glm::vec3(0.0f, 0.0f, 20.0f));

int main()
{
	GLFWwindow* window = initializeGLFWWindow();
	if (window == NULL)
	{
		return -1;
	}
	/*unsigned int texID = texManager.loadTexture("Assets/Textures/checkerboard.png");*/
	//Cube board(&camera, texID);
	initializeCamera();
	//ObjectLoader* objLoader = new ObjectLoader();
	//objLoader->load("C:\\Users\\adams\\Desktop\\cube.obj");

	//uniform vec3 lightPos;
	//uniform vec3 lightColor;
	//uniform vec3 objectColor;


	//Shader shader("default.vert", "defaultTex.frag");
	Shader shader("lighting.vert", "lighting.frag");
	



	Model ourModel("C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\cube.obj");
	Model model2("C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\gamepiece.obj");
	Model model3("C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\gamepiece.obj");






	float previousTime = glfwGetTime();
	int frameCount = 0;

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		//shader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", model);
		shader.setFloat("sample", 1);
		shader.setFloat("sampleCount", 1);
		shader.setFloat("textureWidth", 500);


		shader.setVec3("lightPos", glm::vec3(10.0f, 8, 5));
		shader.setVec3("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
		shader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.use();



		float currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0f)
		{

			glfwSetWindowTitle(window, ((std::to_string(1000.0f / frameCount) + "ms to render").c_str()));
			frameCount = 0;
			previousTime += 1.0f;
		}

		// Input
		processInput(window);
		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//board.render(true);
		ourModel.draw(shader);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));	// it's a bit too big for our scene, so scale it down
		shader.setMat4("model", model);
		shader.use();
		model2.draw(shader);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));	// it's a bit too big for our scene, so scale it down
		shader.setMat4("model", model);
		shader.use();
		model3.draw(shader);

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

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Processing keyboard camera movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
}

void initializeCamera()
{
	//camera
}
