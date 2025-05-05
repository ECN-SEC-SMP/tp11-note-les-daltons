#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <iostream>

#include "typedef.h"
#include "Tile.h"
#include "Board.h"
#include "Player.h"
#include "Menu.h"
#include "Robot.h"

class GameManager
{
private:
    Tile* goal_tile;
    Board board;
    std::vector<Player*> players; 
    std::vector<Robot*> robots;

public:
    /* Constructors */
    GameManager();

    /* Getters */
    Tile* getGoalTile();
    std::vector<Player*> getPlayers();
    Player* getPlayer(int index);
    Robot * getRobot(Color color);

    /* Methods */
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    std::string displayBoard();
    void setupRound();
    void processPredictionsInputs();
    void sortPlayersByPredictions();
    void playRound(int player_index);
    void displayResults();
};

#endif /* GAME_MANAGER_H */