#include <stdexcept>
#include <algorithm>
// #include <ctime>
// #include <cstdlib>
// #include <initializer_list>

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
#define NODE_TOP WALL_COLOR "═" RESET
#define NODE_BOTTOM WALL_COLOR "═" RESET
#define NODE_LEFT WALL_COLOR "║" RESET
#define NODE_RIGHT WALL_COLOR "║" RESET
#define NODE_TOP_LEFT WALL_COLOR "╔" RESET
#define NODE_TOP_RIGHT WALL_COLOR "╗" RESET
#define NODE_BOTTOM_LEFT WALL_COLOR "╚" RESET
#define NODE_BOTTOM_RIGHT WALL_COLOR "╝" RESET

#define EMPTY_FRAME RESET "    "

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
    // // TODO: clear constructor
    // this->goal_tile = new Tile(RED, CIRCLE);
    // std::srand(unsigned(std::time(0)));
    // this->robots.push_back(new Robot(RED, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(BLUE, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(GREEN, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
    // this->robots.push_back(new Robot(YELLOW, std::pair<int, int>(std::rand() % 16, std::rand() % 16)));
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

std::string GameManager::displayBoard()
{
    int BOARD_SIZE = 16;

    std::string output = "\n" RESET;
    std::string temp_seperator = "";
    std::string temp_tiles = "";

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_seperator = "";
        temp_tiles = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = this->board.getFrame(x, y);
            bool frame_is_tile = frame.getTile() != nullptr;
            Robot *robot_on_frame = getRobotOnFrame(x, y);

            /* Top left corner of the frame --------------------------------- */

            /* Goal tile displayed in the center of the board */
            if (x == 8 && y == 8)
            {
                temp_seperator += this->goal_tile->getEmoji();
            }
            /* Disabled frames in the middle */
            else if (x == 8 && y == 7)
            {
                temp_seperator += NODE_BOTTOM;
            }
            else if (x == 7 && y == 8)
            {
                temp_seperator += NODE_RIGHT;
            }
            else if (x == 9 && y == 8)
            {
                temp_seperator += NODE_LEFT;
            }
            else if (x == 8 && y == 9)
            {
                temp_seperator += NODE_TOP;
            }
            /* Top left corner */
            else if (x == 0 && y == 0)
            {
                temp_seperator += NODE_TOP_LEFT;
            }
            /* Left border */
            else if (x == 0)
            {
                temp_seperator += NODE_LEFT;
            }
            /* Top border */
            else if (y == 0)
            {
                temp_seperator += NODE_TOP;
            }
            /* Classic node */
            else
            {
                temp_seperator += NODE;
            }

            /* Top wall ----------------------------------------------------- */

            /* No wall if it's the disabled frames in the middle */
            if (x == 7 && y == 8)
            {
                temp_seperator += "    ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += RESET "   ";
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
                if (y == 0)
                {
                    temp_seperator += NODE_TOP_RIGHT;
                }
                else
                {
                    temp_seperator += NODE_RIGHT;
                }
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

            /* TEMP ========================================================= */
            // if (frame.getWalls()[RIGHT])
            // {
            //     temp_tiles += VERTICAL_WALL;
            // }
            // else
            // {
            //     temp_tiles += VERTICAL_GRID;
            // }

            // if (frame.getWalls()[DOWN])
            // {
            //     temp_seperator += HORIZONTAL_WALL;
            // }
            // else
            // {
            //     temp_seperator += HORIZONTAL_GRID;
            // }

            /* ============================================================== */

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
        output += temp_tiles + ANSI_RESET + "\n" + RESET;
    }

    /* Last row */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = this->board.getFrame(x, BOARD_SIZE - 1);
        /* Node */
        if (x == 0)
        {
            temp_seperator += NODE_BOTTOM_LEFT;
        }
        else
        {
            temp_seperator += NODE_BOTTOM;
        }

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
    temp_seperator += NODE_BOTTOM_RIGHT;

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
