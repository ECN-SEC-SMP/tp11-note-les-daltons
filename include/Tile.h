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
        case Color::RED:
            emoji = ANSI_RED + shape_char + ANSI_RESET; // Red
            break;
        case Color::GREEN:
            emoji = ANSI_GREEN + shape_char + ANSI_RESET; // Green
            break;
        case Color::BLUE:
            emoji = ANSI_BLUE + shape_char + ANSI_RESET; // Blue
            break;
        case Color::YELLOW:
            emoji = ANSI_YELLOW + shape_char + ANSI_RESET; // Yellow
            break;
        case Color::RAINBOW:
            emoji = "🌈"; 
            break;
        default:
            emoji = "  "; // Empty tile
            break;
        }
        return emoji;
    }
};
