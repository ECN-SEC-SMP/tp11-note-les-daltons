#include "Robot.h"

Robot::Robot(Color c, std::pair<int, int> p)
    : color(c), position(p) {}

Robot::Robot(Color c, int x, int y)
    : color(c), position(std::make_pair(x, y)) {}

Color Robot::getColor()
{
    return this->color;
}

std::pair<int, int> Robot::getPosition()
{
    return this->position;
}

int Robot::getX()
{
    return this->position.first;
}

int Robot::getY()
{
    return this->position.second;
}

void Robot::move(int dx, int dy)
{
    position.first += dx;
    position.second += dy;
}