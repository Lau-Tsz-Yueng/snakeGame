// main.cpp
#include <vector>
#include <deque>
#include <iostream>
#include "Wall.h"
#include "Food.h"
#include "PauseWindow.h"
#include "config.h"

using namespace sf;
using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int main()
{
    // 创建一个窗口
    RenderWindow window(VideoMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT), "Snake Game");

    // 创建一个蛇
    deque<RectangleShape> snake;
    RectangleShape segment(Vector2f(CUBE_SIZE, CUBE_SIZE));
    segment.setFillColor(Color::Green);
    segment.setPosition(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_WIDTH / 2);
    snake.push_back(segment);

    // 创建食物
    Food foodObj;
    foodObj.resetFoodPosition();
    RectangleShape food = foodObj.getFood();

    // 创建墙
    Wall wall;
    wall.createWalls();

    // 设置蛇的移动速度
    int speed = CUBE_SIZE;

    // 设置蛇的移动方向
    int dx = 0, dy = 0;
    Direction currentDirection = RIGHT;

    // 设置变量
    bool directionChanged = false;

    // 主循环
    while (window.isOpen())
    {
        Event event;
        int snakeSize = snake.size();
        Vector2f lastSnakePartPosition = snake.back().getPosition();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Pause the game when escape key is pressed
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                bool gamePaused = true;
                PauseWindow pauseWindow;

                while (gamePaused)
                {
                    // 界面渲染
                    window.clear();

                    for (int i = 0; i < snake.size(); i++)
                    {
                        window.draw(snake[i]);
                    }
                    window.draw(food);

                    // Draw the walls
                    for (const auto &segment : wall.walls)
                    {
                        window.draw(segment);
                    }

                    // Draw the Paused Window
                    pauseWindow.draw(window);

                    window.display();

                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                        {
                            gamePaused = false;
                        }

                        if (event.type == Event::Closed)
                        {
                            window.close();
                            gamePaused = false;
                        }
                    }
                }
            }

            // 检测按键
            if (event.type == Event::KeyPressed && !directionChanged)
            {
                if (event.key.code == Keyboard::W && dy == 0)
                {
                    dx = 0;
                    dy = -speed;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::S && dy == 0)
                {
                    dx = 0;
                    dy = speed;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::A && dx == 0)
                {
                    dx = -speed;
                    dy = 0;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::D && dx == 0)
                {
                    dx = speed;
                    dy = 0;
                    directionChanged = true;
                }
            }
        }

        // 更新蛇的位置
        for (int i = snakeSize - 1; i > 0; i--)
        {
            snake[i].setPosition(snake[i - 1].getPosition());
        }
        snake[0].move(dx, dy);

        // 检测蛇是否吃到食物
        if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds()))
        {
            // reset food position in random manner
            foodObj.resetFoodPosition();
            food = foodObj.getFood();

            // print messages:
            cout << "YOUR Current Length is: " << snakeSize << endl;

            // 添加新的一段到蛇的末尾
            RectangleShape tmpSegment(Vector2f(CUBE_SIZE, CUBE_SIZE));
            tmpSegment.setFillColor(Color::Green);
            tmpSegment.setPosition(lastSnakePartPosition);
            snake.push_back(tmpSegment);
        }
        // 检测蛇是否撞墙
        for (auto &tmp : wall.walls)
        {
            if (snake[0].getGlobalBounds().intersects(tmp.getGlobalBounds()))
            {
                cout << "GAME OVER!" << endl;
                cout << "YOUR MAXIMUM LENGTH IS : " << snakeSize << endl;
                window.close();
            }
        }

        // 检测蛇是否咬到自己
        for (int i = 1; i < snakeSize; ++i)
        {
            if (snake[0].getGlobalBounds().intersects(snake[i].getGlobalBounds()))
            {
                cout << "GAME OVER!" << endl;
                cout << "YOUR MAXIMUM LENGTH IS : " << snakeSize << endl;
                window.close();
            }
        }

        // 渲染
        window.clear();

        for (int i = 0; i < snake.size(); i++)
        {
            window.draw(snake[i]);
        }
        window.draw(food);

        // Draw the walls
        for (const auto &segment : wall.walls)
        {
            window.draw(segment);
        }

        window.display();

        // 暂停
        sleep(milliseconds(TIME_FRAME));

        directionChanged = false;
    }

    return 0;
}
