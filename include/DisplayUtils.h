#pragma once

#include "ANSI.h"

/// @brief Game banner to display above each windows
#define GAME_ASCII_BANNER ANSI_BOLD ANSI_BLUE " ____  _                _          _     ____       _           _   \n\
|  _ \\(_) ___ ___   ___| |__   ___| |_  |  _ \\ ___ | |__   ___ | |_ \n\
| |_) | |/ __/ _ \\ / __| '_ \\ / _ \\ __| | |_) / _ \\| '_ \\ / _ \\| __|\n\
|  _ <| | (_| (_) | (__| | | |  __/ |_  |  _ < (_) | |_) | (_) | |_ \n\
|_| \\_\\_|\\___\\___/ \\___|_| |_|\\___|\\__| |_| \\_\\___/|_.__/ \\___/ \\__|\n\
" ANSI_RESET_BOLD ANSI_ITALIC ANSI_UNDERLINE "By Les Daltons\n\n" ANSI_RESET


/* Colors */
#define BACKGROUND_COLOR ANSI_BG_WHITE
#define GRID_COLOR ANSI_LIGHT_GRAY
#define NODE GRID_COLOR "┼" RESET
#define WALL_COLOR ANSI_BLACK

#define RESET ANSI_RESET BACKGROUND_COLOR

/* Grid */
#define HORIZONTAL_GRID GRID_COLOR "────" RESET
#define VERTICAL_GRID GRID_COLOR "│" RESET

/* DOUBLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_DOUBLE WALL_COLOR "════" RESET
#define VERTICAL_WALL_DOUBLE WALL_COLOR "║" RESET

/* Wall nodes */
#define NODE_MIDDLE_DOUBLE WALL_COLOR "╬" RESET
#define NODE_HORIZONTAL_DOUBLE WALL_COLOR "═" RESET
#define NODE_VERTICAL_DOUBLE WALL_COLOR "║" RESET

#define NODE_TOP_DOUBLE WALL_COLOR "╦" RESET
#define NODE_LEFT_DOUBLE WALL_COLOR "╠" RESET
#define NODE_RIGHT_DOUBLE WALL_COLOR "╣" RESET
#define NODE_BOTTOM_DOUBLE WALL_COLOR "╩" RESET

#define NODE_TOP_LEFT_DOUBLE WALL_COLOR "╔" RESET
#define NODE_TOP_RIGHT_DOUBLE WALL_COLOR "╗" RESET
#define NODE_BOTTOM_LEFT_DOUBLE WALL_COLOR "╚" RESET
#define NODE_BOTTOM_RIGHT_DOUBLE WALL_COLOR "╝" RESET

/* SIMPLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_SIMPLE WALL_COLOR "────" RESET
#define VERTICAL_WALL_SIMPLE WALL_COLOR "│" RESET

/* Wall nodes */
#define NODE_MIDDLE_SIMPLE WALL_COLOR "┼" RESET
#define NODE_HORIZONTAL_SIMPLE WALL_COLOR "─" RESET
#define NODE_VERTICAL_SIMPLE WALL_COLOR "│" RESET

#define NODE_TOP_SIMPLE WALL_COLOR "┬" RESET
#define NODE_LEFT_SIMPLE WALL_COLOR "├" RESET
#define NODE_RIGHT_SIMPLE WALL_COLOR "┤" RESET
#define NODE_BOTTOM_SIMPLE WALL_COLOR "┴" RESET

#define NODE_TOP_LEFT_SIMPLE WALL_COLOR "┌" RESET
#define NODE_TOP_RIGHT_SIMPLE WALL_COLOR "┐" RESET
#define NODE_BOTTOM_LEFT_SIMPLE WALL_COLOR "└" RESET
#define NODE_BOTTOM_RIGHT_SIMPLE WALL_COLOR "┘" RESET

#define EMPTY_FRAME RESET "    "
