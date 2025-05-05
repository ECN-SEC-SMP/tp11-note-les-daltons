#include <iostream>
#include <algorithm>

#include "GameManager.h"
#include "typedef.h"
#include "Menu.h"

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