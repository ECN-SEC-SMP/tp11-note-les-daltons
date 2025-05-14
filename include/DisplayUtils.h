#pragma once

#include "ANSI.h"

/// @brief Game banner to display above each windows
#define GAME_ASCII_BANNER ANSI_BOLD ANSI_BLUE "\
 ____  _                _          _     ____       _           _       \n\
|  _ \\(_) ___ ___   ___| |__   ___| |_  |  _ \\ ___ | |__   ___ | |_ ___ \n\
| |_) | |/ __/ _ \\ / __| '_ \\ / _ \\ __| | |_) / _ \\| '_ \\ / _ \\| __/ __|\n\
|  _ <| | (_| (_) | (__| | | |  __/ |_  |  _ < (_) | |_) | (_) | |_\\__ \n\
|_| \\_\\_|\\___\\___/ \\___|_| |_|\\___|\\__| |_| \\_\\___/|_.__/ \\___/ \\__|___/\n\
" ANSI_RESET_BOLD ANSI_ITALIC ANSI_UNDERLINE "By Les Daltons\n\n" ANSI_RESET

/* Board ==================================================================== */
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

#define EMPTY_FRAME "    "

/* Scoreboard =============================================================== */
#define TOP_LEFT_CORNER "┌"
#define TOP_RIGHT_CORNER "┐"
#define BOTTOM_LEFT_CORNER "└"
#define BOTTOM_RIGHT_CORNER "┘"
#define HORIZONTAL_BORDER "─"
#define VERTICAL_BORDER "│"

#define MOI_C_PO "\
 __  __       _          _           _       ____           _ \n\
|  \\/  | ___ (_)     ___( ) ___  ___| |_    |  _ \\ ___     | |\n\
| |\\/| |/ _ \\| |    / __|/ / _ \\/ __| __|   | |_) / _ \\    | |\n\
| |  | | (_) | |   | (__  |  __/\\__ \\ |_    |  __/ (_) |   |_|\n\
|_|  |_|\\___/|_|    \\___|  \\___||___/\\__|   |_|   \\___/    (_)\n\
 "

#define PO ANSI_RED "\
              .-\"-.                 \n\
             ( (_) )                \n\
              `. .'                 \n\
               | |                  \n\
           ..--\" \"--..              \n\
         .' .-'\" \"`-. `.            \n\
   .-.  / .'         `. \\  .-.      \n\
   ||\\`/ /  __     __  \\ \\'/||      \n\
   || `||  /(_|   |(_\\  ||' ||      \n\
   \\  ||  `--'   `--'  ||  //       \n\
    \\_\\ \\      Y      / /_//        \n\
     `--`.`. `.-^-.' .'.'--'        \n\
          > `-.`='.-' <             \n\
        .'             `.           \n\
         `-._________.-'            \n" ANSI_RESET
