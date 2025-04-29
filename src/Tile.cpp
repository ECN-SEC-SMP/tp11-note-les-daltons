#include "Tile.h"

Tile::Tile(Color c, Shape s)
 : color(c), shape(s) {}

Color Tile::getColor(){
    return this->color;
}

Shape Tile::getShape(){
    return this->shape;
}
