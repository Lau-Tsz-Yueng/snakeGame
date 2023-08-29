// Food.cpp
#include "Food.h"

Food::Food() {
    food.setSize(Vector2f(CUBE_SIZE, CUBE_SIZE));
    food.setFillColor(Color::Red);
    srand(time(0));
    int x_coordinate;
    int y_coordinate;
}

int Food::createRandomNumber(int from, int end) {
    std::random_device rd;  // 用于获取随机数的随机数生成器
    std::mt19937 mt(rd());  // 用Mersenne Twister算法初始化随机数生成器
    std::uniform_int_distribution<int> dist(from, end);  // 定义一个范围从10到20的分布
    return dist(mt);
}

void Food::resetFoodPosition() {
    // set random position for food
    int x_axis = createRandomNumber(CUBE_SIZE * 2, WINDOW_SIZE_WIDTH - CUBE_SIZE * 2);
    int y_axis = createRandomNumber(CUBE_SIZE * 2, WINDOW_SIZE_HEIGHT - CUBE_SIZE * 2);

    // make sure the position is a multiple of CUBE_SIZE
    x_axis = x_axis - (x_axis % CUBE_SIZE);
    y_axis = y_axis - (y_axis % CUBE_SIZE);
    // cout << x_axis << " " << y_axis << endl;

    this->food.setPosition(x_axis, y_axis);
}

RectangleShape Food::getFood() {
    return food;
}