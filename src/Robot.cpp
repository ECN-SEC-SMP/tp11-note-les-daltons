#include "Robot.h"

/* Constructor */
Robot::Robot(Color c, std::pair<int, int> p)
    : color(c), position(p) {}

Robot::Robot(Color c, int x, int y)
    : color(c), position(std::make_pair(x, y)) {}

/* Getters */
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

std::string Robot::getEmoji()
{
    switch (this->color)
    {
    case Color::RED:
        return "🔴"; // Red
    case Color::GREEN:
        return "🟢"; // Green
    case Color::BLUE:
        return "🔵"; // Blue
    case Color::YELLOW:
        return "🟡"; // Yellow
    default:
        return "  "; // Empty tile
    }
}

/* Methods */
void Robot::move(int x, int y)
{
    position.first += x;
    position.second += y;
}

void Robot::move(Direction d)
{
    switch (d)
    {
    case UP:
        position.second--;
        break;
    case DOWN:
        position.second++;
        break;
    case LEFT:
        position.first--;
        break;
    case RIGHT:
        position.first++;
        break;
    }
}