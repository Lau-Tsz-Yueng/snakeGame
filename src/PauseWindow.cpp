// PauseWindow.cpp
#include "PauseWindow.h"

PauseWindow::PauseWindow()
{
    RectangleShape pauseOverlay(Vector2f(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT));
    pauseOverlay.setFillColor(Color(255, 0, 0, 128));

    font.loadFromFile("resources/fonts/BlackOpsOne-Regular.ttf");

    pauseText.setFont(font);
    pauseText.setString("GAME PAUSED - Press ESC back to the game");
    pauseText.setCharacterSize(30);
    pauseText.setFillColor(Color::White);

    float x = WINDOW_SIZE_WIDTH / 2 - pauseText.getGlobalBounds().width / 2;
    float y = WINDOW_SIZE_HEIGHT / 2 - pauseText.getGlobalBounds().height / 2;
    pauseText.setPosition(x, y);
}

void PauseWindow::draw(sf::RenderWindow &window)
{
    window.draw(pauseOverlay);
    window.draw(pauseText);
}
