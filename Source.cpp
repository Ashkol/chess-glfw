#include "lighting.h"

Light::Light(glm::vec3 position, glm::vec3 color, float intensity)
{
	this->Position = position;
	this->Color = color;
	this->Intensity = intensity;
}