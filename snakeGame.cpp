#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <iostream>
#include <random>

#define WINDOW_SIZE_WIDTH 800
#define WINDOW_SIZE_HEIGHT 600
#define CUBE_SIZE 20
#define TIME_FRAME 200

using namespace sf;
using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Wall {
public:
    void createWalls() {
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
    vector<RectangleShape> walls;
};

class Food {
public:
    RectangleShape food;
    Food() {
        food.setSize(Vector2f(CUBE_SIZE, CUBE_SIZE));
        food.setFillColor(Color::Red);
        srand(time(0));
        int x_coordinate;
        int y_coordinate;
    }

    int createRandomNumber(int from, int end) {
        std::random_device rd;  // 用于获取随机数的随机数生成器
        std::mt19937 mt(rd());  // 用Mersenne Twister算法初始化随机数生成器
        std::uniform_int_distribution<int> dist(from, end);  // 定义一个范围从10到20的分布
        return dist(mt);
    }

    void resetFoodPosition() {
        // set random position for food
        int x_axis = createRandomNumber(CUBE_SIZE * 2, WINDOW_SIZE_WIDTH - CUBE_SIZE * 2);
        int y_axis = createRandomNumber(CUBE_SIZE * 2, WINDOW_SIZE_HEIGHT - CUBE_SIZE * 2);

        // make sure the position is a multiple of CUBE_SIZE
        x_axis = x_axis - (x_axis % CUBE_SIZE);
        y_axis = y_axis - (y_axis % CUBE_SIZE);
        // cout << x_axis << " " << y_axis << endl;

        this->food.setPosition(x_axis, y_axis);
    }

    RectangleShape getFood() {
        return food;
    }
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

            // 检测按键
            if (event.type == Event::KeyPressed && !directionChanged)
            {
                if (event.key.code == Keyboard::W && dy == 0) {
                    dx = 0; dy = -speed;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::S && dy == 0) {
                    dx = 0; dy = speed;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::A && dx == 0) {
                    dx = -speed; dy = 0;
                    directionChanged = true;
                }
                if (event.key.code == Keyboard::D && dx == 0) {
                    dx = speed; dy = 0;
                    directionChanged = true;
                }
            }
        }

        // 更新蛇的位置
        for (int i = snakeSize - 1; i > 0; i--) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }
        snake[0].move(dx, dy);

        cout << "My Current Length is: " << snakeSize << endl;

        // 检测蛇是否吃到食物
        if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
            // reset food position in random manner
            foodObj.resetFoodPosition();
            food = foodObj.getFood();

            // 添加新的一段到蛇的末尾
            RectangleShape tmpSegment(Vector2f(CUBE_SIZE, CUBE_SIZE));
            tmpSegment.setFillColor(Color::Green);
            tmpSegment.setPosition(lastSnakePartPosition);
            snake.push_back(tmpSegment);
        }
        // 检测蛇是否撞墙
        for (auto &tmp : wall.walls) {
            if (snake[0].getGlobalBounds().intersects(tmp.getGlobalBounds())) {
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

        for (int i = 0; i < snake.size(); i++) {
            window.draw(snake[i]);
        }
        window.draw(food);

        // Draw the walls
        for (const auto& segment : wall.walls) {
            window.draw(segment);
        }

        window.display();

        // 暂停
        sleep(milliseconds(TIME_FRAME));

        directionChanged = false;
    }

    return 0;
}
