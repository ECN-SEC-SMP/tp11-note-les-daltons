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

#define MOVE_ARROW_UP       "↑"
#define MOVE_ARROW_DOWN     "↓"
#define MOVE_ARROW_LEFT     "←"
#define MOVE_ARROW_RIGHT    "→"

class GameManager
{
private:
    /// @brief Tile to go on
    Tile *goal_tile;
    /// @brief Game board
    Board board;
    /// @brief Container of game players
    std::vector<Player *> players;
    /// @brief Container of board robots
    std::vector<Robot *> robots;
    /// @brief Flag to know if round is finished
    bool round_finished = false;
    /// @brief Flag to know if current player has won
    bool cur_player_won = false;
    /// @brief String containing all player moves with colored arrows 
    /// @note "←↑→↓←↑→↓" with color corresponding to the robot that moved
    std::string moves_str = "";

private:
    bool processMovement(Robot *robot, Direction direction, int *deplacement, Menu *m, int player_index);

public:
    /* Constructors */
    GameManager();

    /* Getters */
    /**
     * @brief Get the Goal Tile object
     * 
     * @return Tile* 
     */
    Tile *getGoalTile();
    /**
     * @brief Get the Players container
     * 
     * @return std::vector<Player *> 
     */
    std::vector<Player *> getPlayers();
    /**
     * @brief Get the Player object by index
     * 
     * @param index (IN) Index of player to get (0 to N-1)
     * @return Player* 
     */
    Player *getPlayer(int index);
    /**
     * @brief Get the Board object
     * 
     * @return Board* 
     */
    Board *getBoard();

    /* Methods */
    /**
     * @brief Adds a player to the game.
     *
     * @param player (IN) Pointer to the player to be added.
     */
    void addPlayer(Player *player);
    /**
     * @brief Removes a player from the game.
     *
     * @param player (IN) Pointer to the player to be removed.
     */
    void removePlayer(Player *player);
    /**
     * @brief Returns displayed board string
     *
     * @return std::string
     */
    std::string displayBoard();
    /**
     * @brief Generate or regenerate game board
     */
    void generateBoard();
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
     * 
     * @param player_index (IN) Player index in vector (0: first, 1: second, ...)
     * @return true if player win
     * @return false else
     */
    bool playRound(int player_index);
    /**
     * @brief Displays the results of the game.
     * @note This function is called at the end of the game.
     */
    void displayResults();
    /**
     * @brief Get Robot on frame with (x,y) coordinates
     * 
     * @param x (IN) Coordinate X
     * @param y (IN) Coordinate Y
     * @return Robot* 
     */
    Robot *getRobotOnFrame(int x, int y);
};

#endif /* GAME_MANAGER_H */