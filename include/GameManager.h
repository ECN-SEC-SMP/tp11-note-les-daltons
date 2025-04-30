#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <string>

#include "typedef.h"
#include "Tile.h"
#include "Board.h"
#include "Player.h"

class GameManager
{
private:
    Tile* goal_tile;
    Board board;
    std::vector<Player*> players;

public:
    /* Constructors */
    GameManager();

    /* Getters */
    Tile* getGoalTile();
    std::vector<Player*> getPlayers();
    Player* getPlayer(int index);

    /* Methods */
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    std::string displayBoard();
    void setupRound();
    void processPredictionsInputs();
    void sortPlayersByPredictions();
    void playRound();
    void displayResults();
};

#endif /* GAME_MANAGER_H */