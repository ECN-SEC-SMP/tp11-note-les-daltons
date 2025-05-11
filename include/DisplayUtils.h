#pragma once

/* Colors */
#define BACKGROUND_COLOR ANSI_BG_WHITE
#define GRID_COLOR ANSI_LIGHT_GRAY
#define NODE GRID_COLOR "┼" RESET
#define WALL_COLOR ANSI_BLACK

#define RESET ANSI_RESET BACKGROUND_COLOR

/* Grid */
#define NODE "┼"
#define HORIZONTAL_GRID "────"
#define VERTICAL_GRID "│"

/* DOUBLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_DOUBLE "════"
#define VERTICAL_WALL_DOUBLE "║"

/* Wall nodes */
#define NODE_MIDDLE_DOUBLE "╬"
#define NODE_HORIZONTAL_DOUBLE "═"
#define NODE_VERTICAL_DOUBLE "║"

#define NODE_TOP_DOUBLE "╦"
#define NODE_LEFT_DOUBLE "╠"
#define NODE_RIGHT_DOUBLE "╣"
#define NODE_BOTTOM_DOUBLE "╩"

#define NODE_TOP_LEFT_DOUBLE "╔"
#define NODE_TOP_RIGHT_DOUBLE "╗"
#define NODE_BOTTOM_LEFT_DOUBLE "╚"
#define NODE_BOTTOM_RIGHT_DOUBLE "╝"

/* SIMPLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_SIMPLE "────"
#define VERTICAL_WALL_SIMPLE "│"

/* Wall nodes */
#define NODE_MIDDLE_SIMPLE "┼"
#define NODE_HORIZONTAL_SIMPLE "─"
#define NODE_VERTICAL_SIMPLE "│"

#define NODE_TOP_SIMPLE "┬"
#define NODE_LEFT_SIMPLE "├"
#define NODE_RIGHT_SIMPLE "┤"
#define NODE_BOTTOM_SIMPLE "┴"

#define NODE_TOP_LEFT_SIMPLE "┌"
#define NODE_TOP_RIGHT_SIMPLE "┐"
#define NODE_BOTTOM_LEFT_SIMPLE "└"
#define NODE_BOTTOM_RIGHT_SIMPLE "┘"

#define EMPTY_FRAME RESET "    "
