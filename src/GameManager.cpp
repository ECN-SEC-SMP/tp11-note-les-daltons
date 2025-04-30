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

    std::string output = "";
    std::string temp_seperator = "+----+----+----+----+----+----+----+----+\n";
    std::string temp_tiles = "";
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
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
            if (frame.getTile() != nullptr)
            {
                /* Tile not empty */
                Color frame_tile_color = frame.getTile()->getColor();
                Shape frame_tile_shape = frame.getTile()->getShape();
                temp_tiles += "X";
            }
            else
            {
                /* Tile empty */
                temp_tiles += " ";
            }

            /* Check if it's the last tile of the row */
            if (y == 15)
            {
                temp_tiles += "|";
            }
        }
        output += temp_seperator + "\n";
        output += temp_tiles + "\n";
    }
    /* Bottom wall */
    output += "+----+----+----+----+----+----+----+----+";

    return output;
}