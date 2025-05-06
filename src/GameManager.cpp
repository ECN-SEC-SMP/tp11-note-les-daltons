#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "GameManager.h"
#include "typedef.h"
#include "Menu.h"

/* FONT FORMAT */
#define RESET "\033[0m"
#define GRID_COLOR "\033[38;5;245m"
#define WALL_COLOR "\033[37m"

#define NODE GRID_COLOR "┼" RESET
#define NODE_TOP GRID_COLOR "┬" RESET
#define NODE_BOTTOM GRID_COLOR "┴" RESET
#define NODE_LEFT GRID_COLOR "├" RESET
#define NODE_RIGHT GRID_COLOR "┤" RESET
#define NODE_TOP_LEFT GRID_COLOR "┌" RESET
#define NODE_TOP_RIGHT GRID_COLOR "┐" RESET
#define NODE_BOTTOM_LEFT GRID_COLOR "└" RESET
#define NODE_BOTTOM_RIGHT GRID_COLOR "┘" RESET

#define HORIZONTAL_GRID GRID_COLOR "────" RESET
#define HORIZONTAL_WALL WALL_COLOR "════" RESET
#define VERTICAL_GRID GRID_COLOR "│" RESET
#define VERTICAL_WALL WALL_COLOR "║" RESET
#define DISABLED " " // for disabled frames in the middle of the board

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

            /* Top left corner of the frame --------------------------------- */

            /* Goal tile displayed in the center of the board */
            if (x == 8 && y == 8)
            {
                temp_seperator += "o"; // Tile::getEmojiFromTile(*this->goal_tile);
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
                temp_seperator += " " DISABLED DISABLED " ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += " " DISABLED DISABLED " ";
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
                temp_tiles += DISABLED;
            }
            else if (frame.getWalls()[LEFT])
            {
                temp_tiles += VERTICAL_WALL " ";
            }
            else
            {
                temp_tiles += VERTICAL_GRID " ";
            }

            /* Tile content ------------------------------------------------- */

            /* Disabled tiles in the middle of the board */
            if (x == 7 && y == 7)
            {
                temp_tiles += DISABLED DISABLED DISABLED;
            }
            else if (x == 8 && y == 8)
            {
                temp_tiles += DISABLED DISABLED DISABLED " ";
            }
            else if (x == 7 && y == 8)
            {
                temp_tiles += DISABLED DISABLED DISABLED;
            }
            else if (x == 8 && y == 7)
            {
                temp_tiles += DISABLED DISABLED DISABLED " ";
            }
            else if (frame.getTile() != nullptr)
            {
                /* Tile not empty */
                temp_tiles += Tile::getEmojiFromTile(*frame.getTile()) + " ";
            }
            else
            {
                /* Tile empty */
                temp_tiles += "   ";
            }

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
        output += temp_seperator + "\n";
        output += temp_tiles + "\n";
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

    output += temp_seperator + "\n";

    return output;
}

void GameManager::setupRound()
{
    // Get the goal tile
    int goal_tile_index = rand() % TILES.size();
    this->goal_tile = &TILES[goal_tile_index];

    // Place randomly robots on the board
    for (int i = 0; i < 4; i++)
    {
        int x = rand() % 16;
        if (x == 8)
            x += 1;
        if (x == 7)
            x -= 1;

        int y = rand() % 16;
        if (y == 8)
            x += 1;
        if (y == 7)
            x -= 1;

        this->robots.push_back(Robot(Color(i), std::pair<int, int>(x, y)));
    }
}

bool is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c)
                                      { return !std::isdigit(c); }) == s.end();
}

void GameManager::processPredictionsInputs()
{
    std::cout << this->displayBoard() << std::endl;
    std::cout << std::endl;
    std::cout << "When a player find a solution, press [ENTER] to send your predictions..." << std::endl;
    getchar();
    Menu menu("Predictions inputs:", 1);
    menu.setTimeout(10);
    menu.cancelTimeoutOnKeyPress(false);
    menu.resetTimeoutOnKeyPress(false);
    menu.preventQuitOnEnter(true);
    for (auto &&player : this->players)
    {
        menu.addOption(player->getName());
    }
    menu.run();

    int i = 0;
    for (auto &&prediction_str : menu.getOptionsArgs())
    {
        if (!is_number(prediction_str))
        {
            std::cout << "Prediction for player " << this->players[i]->getName() << " invalid (set to 10)" << std::endl;
        }
        else
        {
            int prediction = std::stoi(prediction_str);
            this->players[i]->setPrediction(prediction);
        }
        i++;
    }
}

void GameManager::sortPlayersByPredictions()
{
    std::sort(this->players.begin(), this->players.end(), [](Player a, Player b)
              { return a.getPrediction() < b.getPrediction(); });
}