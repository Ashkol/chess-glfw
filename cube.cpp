#include "cube.h"
#include <vector>
#include <string>
#include "stb_image.h"
#include <string>
#include <iostream>


Cube::Cube(Camera* camera, unsigned int textureID)
{
	this->camera = camera;
	shader = new Shader("default.vert", "defaultTex.frag");
	stbi_set_flip_vertically_on_load(true);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BASIC_CUBE_VERTICES), BASIC_CUBE_VERTICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(VAO);
};

Cube::~Cube()
{
	if (shader != NULL)
		delete(shader);
}

void Cube::render(bool isRendering)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	float modelArray[16] = { 8.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 8.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 1.0f };
	model = glm::make_mat4(modelArray);
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);
	renderTop();
}

void Cube::setTexture(unsigned int newTextureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, newTextureID);
}

void Cube::setMap(std::vector<std::vector<glm::vec3>> newMap)
{
	map = newMap;
}

void Cube::renderTop()
{
	shader->setFloat("sample", 1);
	shader->setFloat("sampleCount", 1);
	shader->setFloat("textureWidth", 500);
	shader->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}