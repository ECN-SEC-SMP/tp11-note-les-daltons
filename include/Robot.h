#pragma once 

#include <utility>
#include "typedef.h"

class Robot
{
    private:
        Color color;
        std::pair<int, int> position;
    public:
        Robot(Color c, std::pair<int, int> p);
        Robot(Color c, int x, int y);
        Color getColor();
        std::pair<int, int> getPosition();
        int getX();
        int getY();
        void move(int x, int y);
};