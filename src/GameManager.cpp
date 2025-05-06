#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <thread>

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
    this->board.generate();
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

        this->robots.push_back(new Robot(Color(i), x, y));
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
    getchar(); // Wait ENTER pressed

    for (int i = 10; i > 0; i--)
    {
        Menu::clear();
        std::cout << this->displayBoard() << std::endl;
        std::cout << std::endl;
        std::cout << "\033[1mYou have \033[31m" << i << "\033[0m\033[1m seconds to find your solution prdiction...\033[0m" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    Menu menu("Predictions inputs:\n[Press ENTER to comfirm ALL PREDICTION !!]", 0);
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
    std::sort(this->players.begin(), this->players.end(), [](Player* a, Player* b)
              { return a->getPrediction() < b->getPrediction(); });
}