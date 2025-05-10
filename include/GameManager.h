#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <string>

#include "typedef.h"
#include "DisplayUtils.h"
#include "Tile.h"
#include "Board.h"
#include "Player.h"
#include "Robot.h"
#include "Menu.h"

enum WallsStyle
{
    SIMPLE_WALLS,
    DOUBLE_WALLS,
};

enum ColorTheme
{
    LIGHT_THEME,
    DARK_THEME,
};

struct BoardTheme_t
{
    /* Colors */
    std::string background_color = ANSI_WHITE_BG;
    std::string grid_color = ANSI_LIGHT_GRAY;
    std::string wall_color = ANSI_BLACK;
    std::string reset_color = ANSI_RESET + background_color;

    /* Grid */
    std::string node = NODE;
    std::string horizontal_grid = HORIZONTAL_GRID;
    std::string vertical_grid = VERTICAL_GRID;

    /* Walls */
    std::string horizontal_wall;
    std::string vertical_wall;

    /* Wall nodes */
    std::string node_middle;
    std::string node_horizontal;
    std::string node_vertical;

    std::string node_top;
    std::string node_left;
    std::string node_right;
    std::string node_bottom;

    std::string node_top_left;
    std::string node_top_right;
    std::string node_bottom_left;
    std::string node_bottom_right;
};

class GameManager
{
private:
    Tile *goal_tile;
    Board board;
    std::vector<Player*> players;
    std::vector<Robot*> robots;
    BoardTheme_t boardTheme;
    bool round_finished = false; // #TODO: setup in setupRound() method
    bool cur_player_won = false; // #TODO: setup in setupRound() method

private:
    bool processMovement(Robot *robot, Direction direction, int *deplacement, Menu *m, int player_index);

public:
    /* Constructors */
    GameManager();

    /* Getters */
    Tile *getGoalTile();
    std::vector<Player *> getPlayers();
    Player *getPlayer(int index);
    Board *getBoard() { return &this->board; }

    /* Setters */
    void setWallsStyle(WallsStyle wallsStyle);
    void setColorTheme(ColorTheme colorTheme);

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
    std::string displayBoard(bool show_empty = false);
    /**
     * @brief Returns displayed empty board string
     *
     * @return std::string
     */
    std::string displayEmptyBoard();
    /**
     * @brief Generates a random board.
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
     */
    bool playRound(int player_index);
    /**
     * @brief Displays the results of the game.
     * @note This function is called at the end of the game.
     */
    void displayResults();
    Robot* getRobotOnFrame(int x, int y);
    std::string computeNode(Board &board, int x, int y);
};

#endif /* GAME_MANAGER_H */