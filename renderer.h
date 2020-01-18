#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "shader.h"
#include "model.h"
#include "camera.h"
#include "utils.h"
#include "lighting.h"

class Renderer
{
public:
	void render(Camera& camera, Shader& shader, Light& light, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	Model& model;
	Renderer(Model& model);
	//Shader shader;
};

Renderer::Renderer(Model& model) : model(model)
{

}

void Renderer::render(Camera& camera, Shader& shader, Light& light, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scale);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	shader.setMat4("projection", projectionMatrix);
	shader.setMat4("view", viewMatrix);
	shader.setMat4("model", modelMatrix);
	shader.setFloat("sample", 1);
	shader.setFloat("sampleCount", 1);
	shader.setFloat("textureWidth", 500);

	shader.setVec3("lightPos", light.Position);
	shader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("material.ambient", 0.25f, 0.20725f, 0.20725f);
	shader.setVec3("material.diffuse", 0.829f, 0.829f, 0.922f);
	shader.setVec3("material.specular", 0.3f, 0.3f, 0.3f);
	shader.setFloat("material.shininess", 11.264f);
	shader.setVec3("light.ambient", light.Ambient);
	shader.setVec3("light.diffuse", light.Diffuse); // darken the light a bit to fit the scene
	shader.setVec3("light.specular", light.Specular);
	shader.setVec3("viewPos", camera.Position);
	shader.use();

	model.draw(shader);
}

#endif