#pragma once

/* Font formatting with ANSI Escape Sequences */
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[34m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_WHITE "\033[37m"
#define ANSI_RESET "\033[0m"

enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    RAINBOW
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Shape
{
    CIRCLE,
    SQUARE,
    TRIANGLE,
    STAR
};