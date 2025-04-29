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

Tile::Tile(Color c, Shape s)
 : color(c), shape(s) {}

Color Tile::getColor(){
    return this->color;
}

Shape Tile::getShape(){
    return this->shape;
}