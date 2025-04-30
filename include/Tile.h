#pragma once 

#include "typedef.h"


class Tile
{
    private:
        Color color;
        Shape shape;
    public:
        Tile(Color color, Shape shape) : color(color), shape(shape) {}
        Color getColor() const { return color; }
        Shape getShape() const { return shape; }
};