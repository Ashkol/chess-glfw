#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>

class SceneObject
{
public:
	std::string name;
	glm::vec3 worldPosition;
	glm::vec3 scale;
	glm::vec3 rotation;
private:

};

class Component
{

};

class Mesh : public Component
{
public:
private:
	float vertices[1] = { 1.0f };
	glm::mat4 modelMatrix;
};

#endif