#pragma once
#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Game
{
public:
    int board[8][8] =
    { -1,-2,-3,-4,-5,-3,-2,-1,
     -6,-6,-6,-6,-6,-6,-6,-6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      6, 6, 6, 6, 6, 6, 6, 6,
      1, 2, 3, 4, 5, 3, 2, 1 };
    string toChessNotation(int x, int y);
    string toChessNotation(glm::vec3 physCoords);
    int toBoardCoords(string coords);
    int toBoardCoords(glm::vec3 physCoords);
    glm::vec3 toPhysCoords(int x, int y);
    glm::vec3 toPhysCoords(string coords);
    void movePiece(string from, string to);
    void movePiece(int xFrom, int yFrom, int xTo, int yTo);
    void printBoard();

};

// white > 0, black < 0
// 1 rook
// 2 knight
// 3 bishop
// 4 king
// 5 queen
// 6 pawn
int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  1, 2, 3, 4, 5, 3, 2, 1 };

string Game::toChessNotation(int x, int y)
{
    int size = 1;
    std::string s = "";
    s += char(x / size + 97);
    s += char(y / size + 49);
    return s;
}

// Board coordinates are x [0, 7] y [0, 7]
int Game::toBoardCoords(string coords)
{
    int size = 1;
    //int x = int(a) - 97;
    //int y = 7 - int(b) + 49;
    int x = int(coords[0]) - 97;
    int y = int(coords[1]) - 49;
    cout << "Coords: " << coords << "Board coords: " << x << " " << y << endl;
    return x * 10 + y;
}

// Physical coordinates to board coordinates
int Game::toBoardCoords(glm::vec3 physCoords)
{
    int x = physCoords.x * 0.5f + 4.5f;
    int y = physCoords.y * 0.5f + 4.5f;
    return x * 10 + y;
}

// Physical coordinates to chess notation
string Game::toChessNotation(glm::vec3 physCoords)
{
    return toChessNotation(toBoardCoords(physCoords)/ 10, toBoardCoords(physCoords) % 10);
}

glm::vec3 Game::toPhysCoords(int x, int y)
{
    return glm::vec3(x * 2 - 7, 0, -(y * 2 - 7));
}

glm::vec3 Game::toPhysCoords(string coords)
{
    int intCoords = toBoardCoords(coords);
    cout << "Phys Coords = " << toBoardCoords(coords) << endl;
    return toPhysCoords(intCoords / 10, intCoords % 10);
}

void Game::movePiece(string from, string to)
{
    int xFrom = toBoardCoords(from) / 10;
    int yFrom = toBoardCoords(from) % 10;
    int xTo = toBoardCoords(to) / 10;
    int yTo = toBoardCoords(to) % 10;
    cout << "xFrom " << toBoardCoords(from) << "yFrom " << yFrom <<endl;
    cout << "xTo " << toBoardCoords(to) << "yTo " << yTo <<endl;
    movePiece(xFrom, yFrom, xTo, yTo);
}

void Game::movePiece(int xFrom, int yFrom, int xTo, int yTo)
{
    int piece = board[yFrom][xFrom];
    int field = board[yTo][xTo];
    if (piece == 0 || (piece > 0) - (piece < 0) != (field > 0) - (field < 0))
    {
            board[yTo][xTo] =  board[yFrom][xFrom];
             board[yFrom][xFrom] = 0;
    }

}

void Game::printBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "[" << board[7-i][j] << "]";
        }
        cout << endl;
    }
}
#endif 