#include <stdexcept>
#include <algorithm>
#include "GameManager.h"

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
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
    /* TODO: prévoir les 4 tiles éteintes au centre du plateau */

    int BOARD_SIZE = 16;
    std::string disabled_tile = "00 ";

    std::string output = "\n";
    std::string temp_seperator = "";
    std::string temp_tiles = "";
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_seperator = "";
        temp_tiles = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = this->board.getFrame(x, y);
            /* Top wall */
            if (frame.getWalls()[UP])
            {
                temp_seperator += "+----";
            }
            else
            {
                temp_seperator += "+    ";
            }

            /* Left wall */
            if (frame.getWalls()[LEFT])
            {
                temp_tiles += "| ";
            }
            else
            {
                temp_tiles += "  ";
            }

            /* Tile content */

            /* Disabled tiles in the middle of the board */
            if (x == 7 && y == 7)
            {
                temp_tiles += disabled_tile;
            }
            else if (x == 8 && y == 8)
            {
                temp_tiles += disabled_tile;
            }
            else if (x == 7 && y == 8)
            {
                temp_tiles += disabled_tile;
            }
            else if (x == 8 && y == 7)
            {
                temp_tiles += disabled_tile;
            }
            else if (frame.getTile() != nullptr)
            {
                /* Tile not empty */
                temp_tiles += frame.getTile()->getEmojiFromTile(*frame.getTile()) + " ";
            }
            else
            {
                /* Tile empty */
                temp_tiles += "   ";
            }

            /* Last column */
            if (x == BOARD_SIZE - 1)
            {
                if (frame.getWalls()[RIGHT])
                {
                    temp_tiles += "|";
                }
                else
                {
                    temp_tiles += " ";
                }
                temp_seperator += "+";
            }

            /* Last frame (bottom right) */
            if (x == BOARD_SIZE - 1 && y == BOARD_SIZE - 1)
            {
            }
        }
        output += temp_seperator + "\n";
        output += temp_tiles + "\n";
    }

    /* Last row */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = this->board.getFrame(x, BOARD_SIZE - 1);
        if (frame.getWalls()[DOWN])
        {
            temp_seperator += "+----";
        }
        else
        {
            temp_seperator += "+    ";
        }
    }

    /* Bottom right corner */
    temp_seperator += "+";

    output += temp_seperator + "\n\n";

    return output;
}