#pragma once

/* Font formatting with ANSI Escape Sequences */
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[34m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_LIGHT_GRAY "\033[38;5;255m"
#define ANSI_BLACK "\033[30m"
#define ANSI_WHITE_BG "\033[48;5;231m"
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
