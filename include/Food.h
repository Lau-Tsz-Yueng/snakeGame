// Food.h
#pragma once
#include <random>
#include <config.h>

using namespace sf;

class Food
{
public:
    Food();
    int createRandomNumber(int from, int end);
    void resetFoodPosition();
    RectangleShape getFood();

private:
    RectangleShape food;
};
