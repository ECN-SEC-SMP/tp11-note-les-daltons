#pragma once 

#include "typedef.h"


class Tile
{
private:
    Color color;
    Shape shape;
public:
    Tile(Color c, Shape s);
    Color getColor();
    Shape getShape();
};

