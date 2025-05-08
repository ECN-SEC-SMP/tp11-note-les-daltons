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

#define MOVE_ARROW_UP "↑"
#define MOVE_ARROW_DOWN "↓"
#define MOVE_ARROW_LEFT "←"
#define MOVE_ARROW_RIGHT "→"

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
    std::string background_color = ANSI_BG_WHITE;
    std::string grid_color = ANSI_LIGHT_GRAY;
    std::string wall_color = ANSI_BLACK;

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
    /// @brief Coordinate of robots
    std::vector<std::pair<int, int>> robots_coordinates;
    BoardTheme_t boardTheme;

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
    std::string displayBoard();
    /**
     * @brief Generate or regenerate game board
     */
    void generateBoard();
    /**
     * @brief Sets up the game for a new round.
     * @note This function is called at the beginning of each game.
     * @note This function picks up randomly a Goal Tile and setup randomly robots coordinates.
     */
    void setupNewRound();
    /**
     * @brief Sets up the game for a round with last values.
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
    std::string computeNode(int x, int y);
};

#endif /* GAME_MANAGER_H */