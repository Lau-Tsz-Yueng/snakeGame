// Wall.cpp
#include "Wall.h"

void Wall::createWalls() {
    RectangleShape wallSegment(Vector2f(CUBE_SIZE, CUBE_SIZE));
    wallSegment.setFillColor(Color::Blue);

    for (int x = 0; x < WINDOW_SIZE_WIDTH; x += CUBE_SIZE) {
        wallSegment.setPosition(x, 0);
        walls.push_back(wallSegment);
        wallSegment.setPosition(x, WINDOW_SIZE_HEIGHT - CUBE_SIZE);
        walls.push_back(wallSegment);
    }

    for (int y = 0; y < WINDOW_SIZE_HEIGHT; y += CUBE_SIZE) {
        wallSegment.setPosition(0, y);
        walls.push_back(wallSegment);
        wallSegment.setPosition(WINDOW_SIZE_WIDTH - CUBE_SIZE, y);
        walls.push_back(wallSegment);
    }
}
