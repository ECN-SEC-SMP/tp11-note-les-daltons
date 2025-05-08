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
    inline std::string getEmoji() const
    {
        std::string emoji = "";
        std::string shape_char = "";
        switch (this->shape)
        {
        case Shape::CIRCLE:
            shape_char = "● ";
            break;
        case Shape::SQUARE:
            shape_char = "■ ";
            break;
        case Shape::TRIANGLE:
            shape_char = "▲ ";
            break;
        case Shape::STAR:
            shape_char = "🟊 ";
            break;
        default:
            break;
        }

        switch (this->color)
        {
        case RED:
            emoji = "\033[31m" + shape_char + "\033[0m"; // Red
            break;
        case GREEN:
            emoji = "\033[32m" + shape_char + "\033[0m"; // Green
            break;
        case BLUE:
            emoji = "\033[34m" + shape_char + "\033[0m"; // Blue
            break;
        case YELLOW:
            emoji = "\033[33m" + shape_char + "\033[0m"; // Yellow
            break;
        case RAINBOW:
            emoji = "🌈";
            break;
        default:
            emoji = "  "; // Empty tile
            break;
        }
        return emoji;
    }
};