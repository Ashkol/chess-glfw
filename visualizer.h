#pragma once
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "scene.h"

class Visualizer
{
public:
	Scene& scene;
	Visualizer(Scene& scene);
	void render();
private:
	void instantiateBoard();
};

Visualizer::Visualizer(Scene& scene) : scene(scene)
{
	instantiateBoard();
}

void Visualizer::instantiateBoard()
{
	std::string gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\gamepiece.obj";
	std::string gameBoardPath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\cube.obj";

	// White pieces
	for (int i = 0; i < 16; i++)
	{
		SceneObject sceneObject(gamePiecePath);
		sceneObject.Position = glm::vec3(-7 + (i*2 % 16), 0, (i / 8) * 2 - 7);
		scene.addSceneObject(sceneObject);
	}

	//Black pieces
	for (int i = 0; i < 16; i++)
	{
		SceneObject sceneObject(gamePiecePath);
		sceneObject.Position = glm::vec3(-7 + (i * 2 % 16), 0, (i / 8) * 2 + 5);
		scene.addSceneObject(sceneObject);
	}

	// Board
	SceneObject sceneObject(gameBoardPath);
	sceneObject.Position = glm::vec3(0, -1, 0);
	sceneObject.Scale = glm::vec3(8, 1, 8);
	scene.addSceneObject(sceneObject);

	//SceneObject sceneObject(gamePiecePath);
	//SceneObject sceneObject1(gamePiecePath);
	//SceneObject sceneObject2(gamePiecePath);
	//SceneObject sceneObject3(gamePiecePath);
	//sceneObject1.Position = glm::vec3(2, 0, 0);
	//sceneObject2.Position = glm::vec3(-2, 0, 0);
	//sceneObject3.Position = glm::vec3(4, 0, 0);
	//scene.addSceneObject(sceneObject);
	//scene.addSceneObject(sceneObject1);
	//scene.addSceneObject(sceneObject2);
	//scene.addSceneObject(sceneObject3);
}

void Visualizer::render()
{
	scene.render();
}

#endif