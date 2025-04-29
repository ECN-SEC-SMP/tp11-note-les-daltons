#include <stdexcept>
#include <algorithm>
#include "GameManager.h"

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player*>())
{
}

/* Getters */

Tile* GameManager::getGoalTile()
{
    return this->goal_tile;
}

std::vector<Player*> GameManager::getPlayers()
{
    return this->players;
}

Player* GameManager::getPlayer(int index)
{
    if (index < 0 || index >= (int)this->players.size())
    {
        throw std::out_of_range("Index out of range");
    }
    return players[index];
}

/* Methods */

void GameManager::addPlayer(Player* player)
{
    this->players.push_back(player);
}

void GameManager::removePlayer(Player* player)
{
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
}
