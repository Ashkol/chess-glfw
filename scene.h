#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "camera.h"
#include "renderer.h"
#include "lighting.h"

using namespace std;

class SceneObject
{
public:
	std::string Name = "";
	std::string boardCoords = "";
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	//vector<Component> components;
	Renderer* renderer;
	Model* model;
	void draw(Shader& shader, Light& light);
	SceneObject(string modelPath, string fallbackTexturePath);
	~SceneObject();
	Camera* sceneCamera;

private:

};

class Scene
{
public:
	vector<SceneObject> sceneObjects;
	vector<Shader> shaders;
	Camera& sceneCamera;
	Light* light;
	void render();
	Scene(Camera& camera);
	void addSceneObject(SceneObject& objetc);
};

Scene::Scene(Camera& camera) : sceneCamera(camera)
{
	Shader shader("lighting.vert", "lighting.frag");
	shaders.push_back(shader);
	light = new Light(glm::vec3(0, 10, 0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

void Scene::addSceneObject(SceneObject& object)
{
	object.sceneCamera = &sceneCamera;
	sceneObjects.push_back(object);
}

void Scene::render()
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].draw(shaders[0], *light);
	}
}



SceneObject::SceneObject(string modelPath, string fallbackTexturePath) : Position(glm::vec3(0, 0, 0)), Scale(glm::vec3(1, 1, 1)), Rotation(glm::vec3(0, 0, 0))
{
	model = new Model(modelPath, fallbackTexturePath);
	renderer = new Renderer(*model);

	//Position = glm::vec3(0, 0, 0);
	//Scale = glm::vec3(1, 1, 1);
	//Rotation = glm::vec3(0, 0, 0);
}

SceneObject::~SceneObject()
{
	//if (model != NULL)
	//{
	//	free(model);
	//}
	//free(renderer);
}

void SceneObject::draw(Shader& shader, Light& light)
{
	renderer->render(*sceneCamera, shader, light, Position, Scale, Rotation);
}

//class Component
//{
//
//};

#endif