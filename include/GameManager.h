#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <string>

#include "typedef.h"
#include "Tile.h"
#include "Board.h"
#include "Player.h"
#include "Robot.h"
#include "Menu.h"

class GameManager
{
private:
    Tile* goal_tile;
    Board board;
    std::vector<Player*> players;
    std::vector<Robot*> robots;
    bool round_finished = false; // #TODO: setup in setupRound() method
    bool cur_player_won = false; // #TODO: setup in setupRound() method

private:
    bool processMovement(Robot *robot, Direction direction, int * deplacement, Menu *m, int player_index);

public:
    /* Constructors */
    GameManager();
    ~GameManager();

    /* Getters */
    Tile* getGoalTile();
    std::vector<Player*> getPlayers();
    Player* getPlayer(int index);
    Board* getBoard() { return &this->board; }

    /* Methods */
    /**
     * @brief Adds a player to the game.
     * 
     * @param player (IN) Pointer to the player to be added.
     */
    void addPlayer(Player* player);
    /**
     * @brief Removes a player from the game.
     * 
     * @param player (IN) Pointer to the player to be removed.
     */
    void removePlayer(Player* player);
    /**
     * @brief Returns displayed board string
     * 
     * @return std::string 
     */
    std::string displayBoard();
    /**
     * @brief Sets up the game for a new round.
     * @note This function is called at the beginning of each round.
     */
    void setupRound();
    /**
     * @brief Processes the inputs for the predictions of each player.
     * @note This function is called when the players have to made their predictions.
     */
    void processPredictionsInputs();
    /**
     * @brief Sorts the players based on their predictions.
     * @note This function is called after the players have made their predictions.
     */
    void sortPlayersByPredictions();
    /**
     * @brief Plays a round of the game.
     * @note This function is called to play a round of the game.
     */
    bool playRound(int player_index);
    /**
     * @brief Displays the results of the game.
     * @note This function is called at the end of the game.
     */
    void displayResults();
    Robot* getRobotOnFrame(int x, int y);
};

#endif /* GAME_MANAGER_H */