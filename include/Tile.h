#pragma once

#include <string>

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
    static const std::string& getEmojiFromTile(const Tile& tile)
    {
        std::string emoji;
        std::string shape_char;
        switch (tile.shape)
        {
        case Shape::CIRCLE:
            shape_char = "●";
            break;
        case Shape::SQUARE:
            shape_char = "◼";
            break;
        case Shape::TRIANGLE:
            shape_char = "▲";
            break;
        case Shape::STAR:
            shape_char = "🟊";
            break;
        default:
            break;
        }

        switch (tile.color)
        {
        case Color::RED:
            emoji = "\033[31m" + shape_char + "\033[0m"; // Red
            break;
        case Color::GREEN:
            emoji = "\033[32m" + shape_char + "\033[0m"; // Green
            break;
        case Color::BLUE:
            emoji = "\033[34m" + shape_char + "\033[0m"; // Blue
            break;
        case Color::YELLOW:
            emoji = "\033[33m" + shape_char + "\033[0m"; // Yellow
            break;
        case Color::RAINBOW:
            emoji = "🌈"; 
            break;
        default:
            break;
        }
        return emoji;
    }
};
