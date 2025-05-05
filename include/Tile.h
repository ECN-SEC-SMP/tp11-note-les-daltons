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
    static const std::string &getEmojiFromTile(const Tile &tile)
    {
        std::string emoji;
        std::string shape_char;
        switch (tile.shape)
        {
        case CIRCLE:
            shape_char = "●";
            break;
        case SQUARE:
            shape_char = "◼";
            break;
        case TRIANGLE:
            shape_char = "▲";
            break;
        case STAR:
            shape_char = "🟊";
            break;
        default:
            break;
        }

        switch (tile.color)
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
            break;
        }
        return emoji;
    }
};