#pragma once

/* Font formatting with ANSI Escape Sequences */
#define ANSI_RED                "\033[31m"
#define ANSI_GREEN              "\033[32m"
#define ANSI_BLUE               "\033[34m"
#define ANSI_YELLOW             "\033[33m"
#define ANSI_LIGHT_GRAY         "\033[38;5;255m"
#define ANSI_BLACK              "\033[30m"

#define ANSI_BG_WHITE           "\033[48;5;231m"

#define ANSI_BOLD               "\033[1m"
#define ANSI_RESET_BOLD         "\033[22m"
#define ANSI_ITALIC             "\033[3m"
#define ANSI_RESET_ITALIC       "\033[23m"
#define ANSI_UNDERLINE          "\033[4m"
#define ANSI_RESET_UNDERLINE    "\033[24m"
#define ANSI_BLINKING           "\033[5m"
#define ANSI_RESET_BLINKING     "\033[25m"

#define ANSI_RESET              "\033[0m"

/// @brief Game banner to display above each windows
#define GAME_ASCII_BANNER ANSI_BOLD ANSI_BLUE " ____  _                _          _     ____       _           _   \n\
|  _ \\(_) ___ ___   ___| |__   ___| |_  |  _ \\ ___ | |__   ___ | |_ \n\
| |_) | |/ __/ _ \\ / __| '_ \\ / _ \\ __| | |_) / _ \\| '_ \\ / _ \\| __|\n\
|  _ <| | (_| (_) | (__| | | |  __/ |_  |  _ < (_) | |_) | (_) | |_ \n\
|_| \\_\\_|\\___\\___/ \\___|_| |_|\\___|\\__| |_| \\_\\___/|_.__/ \\___/ \\__|\n\
" ANSI_RESET_BOLD ANSI_ITALIC ANSI_UNDERLINE "By Les Daltons\n\n" ANSI_RESET

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
