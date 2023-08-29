// PauseWindow.h
#pragma once
#include <config.h>

using namespace sf;

class PauseWindow
{
public:
    PauseWindow();
    void draw(sf::RenderWindow &window);

private:
    RectangleShape pauseOverlay;
    Font font;
    Text pauseText;
};