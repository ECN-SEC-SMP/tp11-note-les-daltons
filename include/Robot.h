#pragma once

#include <utility>
#include <string>

#include "typedef.h"

class Robot
{
private:
    Color color;
    std::pair<int, int> position;

public:
    /* Constructors */
    Robot(Color c, std::pair<int, int> p);
    Robot(Color c, int x, int y);

    /* Getters */
    Color getColor();
    std::pair<int, int> getPosition();
    int getX();
    int getY();
    std::string getEmoji();

    /* Methods */
    void move(int x, int y);
    void move(Direction d);
};