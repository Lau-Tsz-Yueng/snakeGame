// Wall.h
#pragma once
#include <vector>
#include <config.h>

using namespace sf;
using namespace std;

class Wall
{
public:
    void createWalls();
    vector<RectangleShape> walls;
};
