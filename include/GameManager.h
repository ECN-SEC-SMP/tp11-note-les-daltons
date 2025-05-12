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
inline std::string WallsStyle_toString(WallsStyle ws)
{
    std::string output = "";
    switch (ws)
    {
    case SIMPLE_WALLS:
        output = "SIMPLE_WALLS";
        break;
    case DOUBLE_WALLS:
        output = "DOUBLE_WALLS";
        break;
    default:
        break;
    }
    return output;
}

enum ColorTheme
{
    LIGHT_THEME,
    DARK_THEME,
    CUSTOM,
};
inline std::string ColorTheme_toString(ColorTheme ct)
{
    std::string output = "";
    switch (ct)
    {
    case LIGHT_THEME:
        output = "LIGHT_THEME";
        break;
    case DARK_THEME:
        output = "DARK_THEME";
        break;
    case CUSTOM:
        output = "CUSTOM";
        break;
    default:
        break;
    }
    return output;
}

enum ScoreboardColumns
{
    RANK_COLUMN,
    NAME_COLUMN,
    ROUNDS_COLUMN,
    SCORE_COLUMN,
    SUCCESS_COLUMN
};

struct BoardTheme_t
{
    /* Colors */
    std::string background_color = ANSI_BG_WHITE;
    std::string grid_color = ANSI_LIGHT_GRAY;
    std::string wall_color = ANSI_BLACK;
    std::string reset_color = ANSI_RESET + background_color;
    std::string menu_selection_color = ANSI_GREEN;
    std::string menu_robot_selected_color = ANSI_RED;

    ColorTheme color_theme;

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

    WallsStyle walls_style;
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
    /// @brief Winner of a round;
    Player *winner = nullptr;
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
    /// @brief Board Theme Structure to store all colors and strings
    BoardTheme_t boardTheme;
    bool replace_robots_each_round = false;

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
     * @return Board&
     */
    Board &getBoard();
    /**
     * @brief Get the board theme structure
     * 
     * @return BoardTheme_t&
     */
    BoardTheme_t &getBoardTheme();
    /**
     * @brief Get if robots are replaced each round
     * 
     * @return bool
     */
    bool robotsAreReplacedEachRound() const;

    /* Setters */
    void setWinner(Player *player);
    /**
     * @brief Set the walls style
     * 
     * @param wallsStyle (IN) New Walls Style
     */
    void setWallsStyle(WallsStyle wallsStyle);
    /**
     * @brief Set the color theme
     * 
     * @param colorTheme (IN) New Color Theme
     */
    void setColorTheme(ColorTheme colorTheme);
    /**
     * @brief Set if robots must be replaced each round
     * 
     * @param replace_robots_each_round 
     */
    void replaceRobotsEachRound(bool replace_robots_each_round);

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
     * @note This function is called at the beginning of each game.
     * @note This function picks up randomly a Goal Tile and setup randomly robots coordinates.
     */
    void setupRound();
    /**
     * @brief Sets up the game for a round with last values.
     * @note This function is called at the beginning of each round.
     */
    void resetRound();
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
     * @brief Sorts players according to their score in descending order
     * @note This function is called when displaying results of a round.
     */
    void sortPlayersByScore();
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
     * @brief Displays the results of the round.
     * @note This function is called at the end of each round.
     */
    std::string displayRoundResults();
    /**
     * @brief Displays the scoreboard.
     * @note This function is called in the sub menu "Stats".
     */
    std::string displayScoreboard();
    /**
     * @brief Get Robot on frame with (x,y) coordinates
     *
     * @param x (IN) X coordinates
     * @param y (IN) Y coordinates
     * @return Robot*
     */
    Robot *getRobotOnFrame(int x, int y);
    /**
     * @brief Get node string after computing it by walls around
     * 
     * @param board (IN) Board Reference
     * @param x (IN) X coordinates of the bottom-right frame
     * @param y (IN) Y coordinates of the bottom-right frame
     * @return std::string 
     */
    std::string computeNode(Board &board, int x, int y);
};

#endif /* GAME_MANAGER_H */