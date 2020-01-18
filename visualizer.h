#pragma once
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "scene.h"
#include "game.h"
#include <boost/lexical_cast.hpp>

class Visualizer
{
public:
	Scene& scene;
	Game game;
	Visualizer(Scene& scene);
	void render();
	void makeMove(string from, string to);
private:
	void instantiateBoard();
	SceneObject* getChessPiece(string boardCoords);
};

Visualizer::Visualizer(Scene& scene) : scene(scene)
{
	instantiateBoard();

	Game game;
	game.printBoard();
}

void Visualizer::makeMove(string from, string to)
{
	game.movePiece(from, to);
	getChessPiece(from)->Position = game.toPhysCoords(to);
	game.printBoard();
}

SceneObject*  Visualizer::getChessPiece(string boardCoords)
{
	for (int i = 0; i < scene.sceneObjects.size(); i++)
	{
		if (scene.sceneObjects[i].boardCoords == boardCoords)
			return &scene.sceneObjects[i];
	}
	cout << "Chess piece not found in such coordinates" << endl;
	return NULL;
}

void Visualizer::instantiateBoard()
{
	std::string gamePiecePath = "";
	std::string gameBoardPath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\cube.obj";
	std::string name = "";
	std::string boardCoords = "";
	// White pieces
	for (int i = 0; i < 16; i++)
	{	
		boardCoords = game.toChessNotation((i-8) % 8, (i-8) / 8);

		if (i == 8 || i == 15)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\rook.obj";
			name = "Rook";
		}
		else if (i == 9 || i == 14)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\knight.obj";
			name = "Knight";
		}
		else if (i == 10 || i == 13)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\bishop.obj";
			name = "Bishop";
		}
		else if (i == 11)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\queen.obj";
			name = "Queen";
		}
		else if (i == 12)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\king.obj";
			name = "King";
		}
		else
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\pawn.obj";
			name = "Pawn";
			boardCoords = game.toChessNotation((i+ 8) % 8, (i+8) / 8);
		}

		cout << boardCoords;
		SceneObject sceneObject(gamePiecePath, "Assets/Textures/white.png");
		sceneObject.Name = "White " + name;
		sceneObject.boardCoords = boardCoords;
		sceneObject.Position = glm::vec3(-7 + (i * 2 % 16), 0, (i / 8) * 2 + 5);
		scene.addSceneObject(sceneObject);

	}

	cout << "--- BLACK ---" << endl;
	//Black pieces
	for (int i = 15; i >= 0; i--)
	{
		boardCoords = game.toChessNotation((i+48) % 8, (i + 48)  / 8);

		if (i == 0 || i == 7)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\rook.obj";
			name = "Rook";
		}
		else if (i == 1 || i == 6)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\knight.obj";
			name = "Knight";
		}
		else if (i == 2 || i == 5)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\bishop.obj";
			name = "Bishop";
		}
		else if (i == 3)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\queen.obj";
			name = "Queen";
		}
		else if (i == 4)
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\king.obj";
			name = "King";
		}
		else
		{
			gamePiecePath = "C:\\Users\\adams\\source\\repos\\Checkers\\Checkers\\Assets\\Models\\pawn.obj";
			name = "Pawn";
		}

		cout << boardCoords;
		SceneObject sceneObject(gamePiecePath, "Assets/Textures/black.png");
		sceneObject.Name = "Black " + name;
		sceneObject.boardCoords = boardCoords;
		sceneObject.Position = glm::vec3(-7 + (i * 2 % 16), 0, (i / 8) * 2 - 7);
		scene.addSceneObject(sceneObject);
		if (i == 1 || i == 6)
			scene.sceneObjects[scene.sceneObjects.size() - 1].Rotation = glm::vec3(0, 180, 0);
	}

	// Board
	SceneObject sceneObject(gameBoardPath, "Assets/Textures/checkerboard.png");
	sceneObject.Position = glm::vec3(0, -1, 0);
	sceneObject.Scale = glm::vec3(8, 1, 8);
	scene.addSceneObject(sceneObject);
}

void UpdateRenderedScene()
{

}

void Visualizer::render()
{
	scene.render();
}

#endif