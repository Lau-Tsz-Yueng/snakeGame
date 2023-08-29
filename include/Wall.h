// Wall.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define CUBE_SIZE 20
#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600

using namespace sf;
using namespace std;

class Wall {
public:
    void createWalls();
    vector<RectangleShape> walls;
};
