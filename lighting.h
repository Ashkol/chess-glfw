#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Light
{
public:
	glm::vec3 Position;
	glm::vec3 Color;
	float Intensity;
	Light(glm::vec3 position, glm::vec3 color, float intensity);
private:
};
#endif