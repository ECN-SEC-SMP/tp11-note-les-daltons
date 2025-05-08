#include <stdexcept>
#include <algorithm>
/* TEMP ===================================================================== */
// #define SHOW_DOUBLE_WALLS
#include <ctime>
#include <cstdlib>
#include <initializer_list>
/* ========================================================================== */

#include "typedef.h"
#include "GameManager.h"

#define RESET ANSI_RESET ANSI_WHITE_BG

/* Grid style */
#define GRID_COLOR ANSI_LIGHT_GRAY
#define HORIZONTAL_GRID GRID_COLOR "────" RESET
#define VERTICAL_GRID GRID_COLOR "│" RESET

/* Wall style */
#define WALL_COLOR ANSI_BLACK
#define HORIZONTAL_WALL WALL_COLOR "════" RESET
#define VERTICAL_WALL WALL_COLOR "║" RESET

/* Node styles */
#define NODE GRID_COLOR "┼" RESET
#define NODE_MIDDLE WALL_COLOR "╬" RESET
#define NODE_HORIZONTAL WALL_COLOR "═" RESET
#define NODE_VERTICAL WALL_COLOR "║" RESET

#define NODE_TOP WALL_COLOR "╦" RESET
#define NODE_LEFT WALL_COLOR "╠" RESET
#define NODE_RIGHT WALL_COLOR "╣" RESET
#define NODE_BOTTOM WALL_COLOR "╩" RESET

#define NODE_TOP_LEFT WALL_COLOR "╔" RESET
#define NODE_TOP_RIGHT WALL_COLOR "╗" RESET
#define NODE_BOTTOM_LEFT WALL_COLOR "╚" RESET
#define NODE_BOTTOM_RIGHT WALL_COLOR "╝" RESET

#define EMPTY_FRAME RESET "    "

#define BOARD_SIZE 16

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
    /* TEMP ================================================================= */
    // this->goal_tile = new Tile(RED, CIRCLE);
    // std::srand(unsigned(std::time(0)));
    // this->robots.push_back(new Robot(RED, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(BLUE, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(GREEN, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(YELLOW, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    /* ====================================================================== */
}

/* Getters */

Tile *GameManager::getGoalTile()
{
    return this->goal_tile;
}

std::vector<Player *> GameManager::getPlayers()
{
    return this->players;
}

Player *GameManager::getPlayer(int index)
{
    if (index < 0 || index >= (int)this->players.size())
    {
        throw std::out_of_range("Index out of range");
    }
    return players[index];
}

/* Methods */

void GameManager::addPlayer(Player *player)
{
    this->players.push_back(player);
}

void GameManager::removePlayer(Player *player)
{
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
}

std::string GameManager::computeNode(int x, int y)
{
    /* Get the frames around to the node */
    /*
                   XXXX¦                     ¦XXXX
        top_left:  ----+----   top:      ----+----
                       ¦                     ¦    

                       ¦                     ¦    
        left:      ----+----   current:  ----+----
                   XXXX¦                     ¦XXXX
    */
    Frame current_frame = this->board.getFrame(x, y);
    Frame left_frame = this->board.getFrame(x - 1, y);
    Frame top_left_frame = this->board.getFrame(x - 1, y - 1);
    Frame top_frame = this->board.getFrame(x, y - 1);

    /* Get the walls around the node */
    /*
                  ║                   ¦    
        top:  ----+----   bottom: ----+----
                  ¦                   ║    

                  ¦                   ¦    
        left: ════+----   right:  ----+════
                  ¦                   ¦    
    */

    bool left_wall;
    bool right_wall;
    bool top_wall;
    bool bottom_wall;

    if (x == 0)
    {
        left_wall = false;
        right_wall = current_frame.getWalls()[UP];
    }
    else if (x == BOARD_SIZE)
    {
        top_wall = top_left_frame.getWalls()[RIGHT];
        left_wall = left_frame.getWalls()[UP];
        right_wall = false;
        bottom_wall = left_frame.getWalls()[RIGHT];
    }
    else
    {
        left_wall = left_frame.getWalls()[UP];
        right_wall = current_frame.getWalls()[UP];
    }

    if (y == 0)
    {
        top_wall = false;
        if (x != BOARD_SIZE)
        {
            bottom_wall = current_frame.getWalls()[LEFT];
        }
    }
    else if (y == BOARD_SIZE)
    {
        if (x != BOARD_SIZE)
        {
            top_wall = top_frame.getWalls()[LEFT];
            right_wall = top_frame.getWalls()[DOWN];
        }
        left_wall = top_left_frame.getWalls()[DOWN];
        bottom_wall = false;
    }
    else if (x != BOARD_SIZE)
    {
        top_wall = top_frame.getWalls()[LEFT];
        bottom_wall = current_frame.getWalls()[LEFT];
    }

    std::string node;
    /* Goal tile displayed in the center of the board */
    if (x == 8 && y == 8)
    {
        if (this->goal_tile == nullptr)
        {
            throw std::runtime_error("Goal tile is not set");
        }
        node = this->goal_tile->getEmoji();
    }
    else
    {
        if (top_wall && left_wall && bottom_wall && right_wall)
        {
            node = NODE_MIDDLE;
        }

        else if (left_wall && right_wall && !top_wall && !bottom_wall) 
        {
            node = NODE_HORIZONTAL;
        }
        else if (top_wall && bottom_wall && !left_wall && !right_wall) 
        {
            node = NODE_VERTICAL;
        }

        else if (bottom_wall && right_wall && !top_wall && !left_wall)
        {
            node = NODE_TOP_LEFT;
        }
        else if (left_wall && bottom_wall && !top_wall && !right_wall)
        {
            node = NODE_TOP_RIGHT;
        }
        else if (top_wall && left_wall && !bottom_wall && !right_wall)
        {
            node = NODE_BOTTOM_RIGHT;
        }
        else if (top_wall && right_wall && !bottom_wall && !left_wall)
        {
            node = NODE_BOTTOM_LEFT;
        }
        
        else if (left_wall && bottom_wall && right_wall && !top_wall)
        {
            node = NODE_TOP;
        }
        else if (left_wall && top_wall && right_wall && !bottom_wall)
        {
            node = NODE_BOTTOM;
        }
        else if (top_wall && right_wall && bottom_wall && !left_wall)
        {
            node = NODE_LEFT;
        }
        else if (top_wall && left_wall && bottom_wall && !right_wall)
        {
            node = NODE_RIGHT;
        }
        else
        {
            node += NODE;
        }
    }

    return node;
}

std::string GameManager::displayBoard()
{
    std::string output = "\n" RESET;
    std::string temp_seperator = "";
    std::string temp_tiles = "";

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_seperator = "";
        temp_tiles = "";
/* TEMP ===================================================================== */
#ifdef SHOW_DOUBLE_WALLS
        temp_seperator += " ";
        temp_tiles += VERTICAL_WALL;
#endif
/* ========================================================================== */
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = this->board.getFrame(x, y);
            bool frame_is_tile = frame.getTile() != nullptr;
            Robot *robot_on_frame = getRobotOnFrame(x, y);

            /* Top left corner of the frame --------------------------------- */
            temp_seperator += computeNode(x, y);

            /* Top wall ----------------------------------------------------- */

            /* No wall if it's the disabled frames in the middle */
            temp_seperator += RESET;
            if (x == 7 && y == 8)
            {
                temp_seperator += "    ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += "   ";
            }
            /* Classic wall */
            else if (frame.getWalls()[UP])
            {
                temp_seperator += HORIZONTAL_WALL;
            }
            /* No wall */
            else
            {
                temp_seperator += HORIZONTAL_GRID;
            }

            /* Add right node if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                temp_seperator += computeNode(x + 1, y);
            }

            /* Left wall ---------------------------------------------------- */
            if ((x == 8 && y == 7) || (x == 8 && y == 8))
            {
                /* No walls in the middle of the board */
                temp_tiles += " ";
            }
            else if (frame.getWalls()[LEFT])
            {
                temp_tiles += VERTICAL_WALL;
            }
            else
            {
                temp_tiles += VERTICAL_GRID;
            }

            /* Tile content ------------------------------------------------- */

            /* Disabled tiles in the middle of the board */
            if ((x == 7 && y == 7) || (x == 8 && y == 7) || (x == 7 && y == 8) || (x == 8 && y == 8))
            {
                temp_tiles += EMPTY_FRAME;
            }
            else if (frame_is_tile || robot_on_frame)
            {
                /* Robot on the frame, and frame is a tile */
                if (frame_is_tile && robot_on_frame)
                {
                    temp_tiles += frame.getTile()->getEmoji() + robot_on_frame->getEmoji();
                }

                /* Robot on the frame */
                else if (robot_on_frame)
                {
                    temp_tiles += " " + robot_on_frame->getEmoji() + " ";
                }

                /* Frame is a tile */
                else if (frame_is_tile)
                {
                    temp_tiles += " " + frame.getTile()->getEmoji() + " ";
                }
            }
            else
            {
                /* Frame empty */
                temp_tiles += EMPTY_FRAME;
            }

/* TEMP ===================================================================== */
#ifdef SHOW_DOUBLE_WALLS
            temp_seperator += NODE;
            if (frame.getWalls()[RIGHT])
            {
                temp_tiles += VERTICAL_WALL;
            }
            else
            {
                temp_tiles += VERTICAL_GRID;
            }
#endif
/* ========================================================================== */

            /* Add right wall if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                if (frame.getWalls()[RIGHT])
                {
                    temp_tiles += VERTICAL_WALL;
                }
                else
                {
                    temp_tiles += VERTICAL_GRID;
                }
            }
        }
        output += temp_seperator + ANSI_RESET + "\n" + RESET;
/* TEMP ===================================================================== */
#ifdef SHOW_DOUBLE_WALLS
        temp_seperator = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = this->board.getFrame(x, y);
            /* Node */
            temp_seperator += computeNode(x + 1, y + 1);
            temp_seperator += computeNode(x + 1, y + 1);

            /* Wall */
            if (frame.getWalls()[DOWN])
            {
                temp_seperator += HORIZONTAL_WALL;
            }
            else
            {
                temp_seperator += HORIZONTAL_GRID;
            }

            /* Last column */
            if (x == BOARD_SIZE - 1)
            {
                temp_seperator += computeNode(BOARD_SIZE, y);
            }
        }
        output += temp_seperator + ANSI_RESET + "\n" + RESET;
#endif
/* ========================================================================== */
        output += temp_tiles + ANSI_RESET + "\n" + RESET;
    }

    /* Bottom border of the board */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = this->board.getFrame(x, BOARD_SIZE - 1);
        /* Node */
        temp_seperator += computeNode(x, BOARD_SIZE);

        /* Wall */
        if (frame.getWalls()[DOWN])
        {
            temp_seperator += HORIZONTAL_WALL;
        }
        else
        {
            temp_seperator += HORIZONTAL_GRID;
        }
    }

    /* Bottom right corner */
    temp_seperator += computeNode(BOARD_SIZE, BOARD_SIZE);

    output += temp_seperator + ANSI_RESET + "\n";

    return output;
}

Robot *GameManager::getRobotOnFrame(int x, int y)
{
    for (Robot *robot : this->robots)
    {
        if (robot->getX() == x && robot->getY() == y)
        {
            return robot;
        }
    }
    return nullptr;
}
