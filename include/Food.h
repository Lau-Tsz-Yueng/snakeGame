// Food.h
#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#define CUBE_SIZE 20
#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600

using namespace sf;

class Food {
public:
    Food();
    int createRandomNumber(int from, int end);
    void resetFoodPosition();
    RectangleShape getFood();
private:
    RectangleShape food;
};
