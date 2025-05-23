#include <stdexcept>
#include <algorithm>
#include <numeric>

#ifdef _WIN32 // Windows sucks
#include <conio.h>
#endif

#include "GameManager.h"
#include "Utils.h"
#include "ANSI.h"
#include "DisplayUtils.h"

#define BOARD_SIZE 16

/* Constructors */
GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
    this->setWallsStyle(SIMPLE_WALLS);
    this->setColorTheme(LIGHT_THEME);
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
Board &GameManager::getBoard()
{
    return this->board;
}

/* Setters */

BoardTheme_t &GameManager::getBoardTheme()
{
    return this->boardTheme;
}

bool GameManager::robotsAreReplacedEachRound() const
{
    return this->replace_robots_each_round;
}

void GameManager::setWallsStyle(WallsStyle wallsStyle)
{
    switch (wallsStyle)
    {
    case SIMPLE_WALLS:
        this->boardTheme.horizontal_wall = HORIZONTAL_WALL_SIMPLE;
        this->boardTheme.vertical_wall = VERTICAL_WALL_SIMPLE;

        this->boardTheme.node_middle = NODE_MIDDLE_SIMPLE;
        this->boardTheme.node_horizontal = NODE_HORIZONTAL_SIMPLE;
        this->boardTheme.node_vertical = NODE_VERTICAL_SIMPLE;

        this->boardTheme.node_top = NODE_TOP_SIMPLE;
        this->boardTheme.node_left = NODE_LEFT_SIMPLE;
        this->boardTheme.node_right = NODE_RIGHT_SIMPLE;
        this->boardTheme.node_bottom = NODE_BOTTOM_SIMPLE;

        this->boardTheme.node_top_left = NODE_TOP_LEFT_SIMPLE;
        this->boardTheme.node_top_right = NODE_TOP_RIGHT_SIMPLE;
        this->boardTheme.node_bottom_left = NODE_BOTTOM_LEFT_SIMPLE;
        this->boardTheme.node_bottom_right = NODE_BOTTOM_RIGHT_SIMPLE;
        break;

    case DOUBLE_WALLS:
        this->boardTheme.horizontal_wall = HORIZONTAL_WALL_DOUBLE;
        this->boardTheme.vertical_wall = VERTICAL_WALL_DOUBLE;

        this->boardTheme.node_middle = NODE_MIDDLE_DOUBLE;
        this->boardTheme.node_horizontal = NODE_HORIZONTAL_DOUBLE;
        this->boardTheme.node_vertical = NODE_VERTICAL_DOUBLE;

        this->boardTheme.node_top = NODE_TOP_DOUBLE;
        this->boardTheme.node_left = NODE_LEFT_DOUBLE;
        this->boardTheme.node_right = NODE_RIGHT_DOUBLE;
        this->boardTheme.node_bottom = NODE_BOTTOM_DOUBLE;

        this->boardTheme.node_top_left = NODE_TOP_LEFT_DOUBLE;
        this->boardTheme.node_top_right = NODE_TOP_RIGHT_DOUBLE;
        this->boardTheme.node_bottom_left = NODE_BOTTOM_LEFT_DOUBLE;
        this->boardTheme.node_bottom_right = NODE_BOTTOM_RIGHT_DOUBLE;
        break;

    default:
        throw std::invalid_argument("Invalid walls style");
    }
    this->boardTheme.walls_style = wallsStyle;
}

void GameManager::setColorTheme(ColorTheme colorTheme)
{
    switch (colorTheme)
    {
    case LIGHT_THEME:
        this->boardTheme.background_color = ANSI_BG_WHITE;
        this->boardTheme.grid_color = ANSI_LIGHT_GRAY;
        this->boardTheme.wall_color = ANSI_BLACK;
        break;

    case DARK_THEME:
        this->boardTheme.background_color = ANSI_BG_BLACK;
        this->boardTheme.grid_color = ANSI_DARK_GRAY;
        this->boardTheme.wall_color = ANSI_ORANGE;
        break;

    case CUSTOM:
        break;

    default:
        throw std::invalid_argument("Invalid color theme");
        break;
    }

    this->boardTheme.reset_color = ANSI_RESET + this->boardTheme.background_color;
    this->boardTheme.color_theme = colorTheme;
}

void GameManager::replaceRobotsEachRound(bool replace_robots_each_round)
{
    this->replace_robots_each_round = replace_robots_each_round;
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

std::string GameManager::computeNode(Board &_board, int x, int y)
{
    /* Get the frames around to the node */
    /*
                   XXXX¦                     ¦XXXX
        top_left:  ----+----   top:      ----+----
                       ¦                     ¦

                       ¦                     ¦
        left:      ----+----   current:  ----+----
                   XXXX¦                     ¦XXXX
    */
    Frame current_frame = _board.getFrame(x, y);
    Frame left_frame = _board.getFrame(x - 1, y);
    Frame top_left_frame = _board.getFrame(x - 1, y - 1);
    Frame top_frame = _board.getFrame(x, y - 1);

    /* Get the walls around the node */
    /*
                  ║                   ¦
        top:  ----+----   bottom: ----+----
                  ¦                   ║

                  ¦                   ¦
        left: ════+----   right:  ----+════
                  ¦                   ¦
    */
    bool left_wall;
    bool right_wall;
    bool top_wall;
    bool bottom_wall;

    /* Check x coordinate to get left and right walls ----------------------- */
    /* Left border of the board */
    if (x == 0)
    {
        left_wall = false;
        right_wall = current_frame.getWalls()[UP];
    }

    /* Right border of the board */
    else if (x == BOARD_SIZE)
    {
        /* Current and top frames don't exist because x is outside the board. */
        /* Thus, only the left and top-left frames are used to get the walls. */
        top_wall = top_left_frame.getWalls()[RIGHT];
        left_wall = left_frame.getWalls()[UP];
        right_wall = false;
        bottom_wall = left_frame.getWalls()[RIGHT];
    }

    /* Inside the board */
    else
    {
        left_wall = left_frame.getWalls()[UP];
        right_wall = current_frame.getWalls()[UP];
    }

    /* Check y coordinate to get top and bottom walls ----------------------- */
    /* Top boarder of the board */
    if (y == 0)
    {
        top_wall = false;
        /* Don't change bottom_wall when x is outside the board because it has
        already been set when checking the x coordinate */
        if (x != BOARD_SIZE)
        {
            bottom_wall = current_frame.getWalls()[LEFT];
        }
    }

    /* Bottom border of the board */
    else if (y == BOARD_SIZE)
    {
        /* Don't change top_wall and right_wall when x is outside the board
        because it has already been set when checking the x coordinate */
        if (x != BOARD_SIZE)
        {
            top_wall = top_frame.getWalls()[LEFT];
            right_wall = top_frame.getWalls()[DOWN];
        }
        /* Left frame doesn't exist because y is outside the board. Thus, the
        top left frame is used to get the left wall */
        left_wall = top_left_frame.getWalls()[DOWN];
        bottom_wall = false;
    }

    /* Inside the board, except the right border because it has already been
    set when checking the x coordinate */
    else if (x != BOARD_SIZE)
    {
        top_wall = top_frame.getWalls()[LEFT];
        bottom_wall = current_frame.getWalls()[LEFT];
    }

    std::string node = "";
    ;
    /* Goal tile displayed in the center of the board */
    if (x == 8 && y == 8)
    {
        if (this->goal_tile == nullptr)
        {
            node += "  ";
        }
        else
        {
            node += this->goal_tile->getEmoji();
        }
    }
    else
    {
        node += this->boardTheme.wall_color;
        if (top_wall && left_wall && bottom_wall && right_wall)
        {
            node += this->boardTheme.node_middle;
        }

        /* Walls */
        else if (left_wall && right_wall && !top_wall && !bottom_wall)
        {
            node += this->boardTheme.node_horizontal;
        }
        else if (top_wall && bottom_wall && !left_wall && !right_wall)
        {
            node += this->boardTheme.node_vertical;
        }

        /* Corners */
        else if (bottom_wall && right_wall && !top_wall && !left_wall)
        {
            node += this->boardTheme.node_top_left;
        }
        else if (left_wall && bottom_wall && !top_wall && !right_wall)
        {
            node += this->boardTheme.node_top_right;
        }
        else if (top_wall && left_wall && !bottom_wall && !right_wall)
        {
            node += this->boardTheme.node_bottom_right;
        }
        else if (top_wall && right_wall && !bottom_wall && !left_wall)
        {
            node += this->boardTheme.node_bottom_left;
        }

        /* Node with 3 walls */
        else if (left_wall && bottom_wall && right_wall && !top_wall)
        {
            node += this->boardTheme.node_top;
        }
        else if (left_wall && top_wall && right_wall && !bottom_wall)
        {
            node += this->boardTheme.node_bottom;
        }
        else if (top_wall && right_wall && bottom_wall && !left_wall)
        {
            node += this->boardTheme.node_left;
        }
        else if (top_wall && left_wall && bottom_wall && !right_wall)
        {
            node += this->boardTheme.node_right;
        }

        /* Grid node */
        else
        {
            node += this->boardTheme.grid_color;
            node += this->boardTheme.node;
        }
    }
    node += this->boardTheme.reset_color;

    return node;
}

std::string GameManager::displayBoard(bool show_empty)
{
    /* Define board to display */
    Board board_to_display = show_empty ? Board::createEmptyBoard() : this->board;

    /* Disable goal tile if empty board displaying requested */
    Tile *save_goal_tile = this->goal_tile;
    if (show_empty)
    {
        this->goal_tile = nullptr;
    }

    std::string output = GAME_ASCII_BANNER "\n" + this->boardTheme.reset_color;
    std::string temp_seperator = "";
    std::string temp_tiles = "";

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_seperator = "";
        temp_tiles = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = board_to_display.getFrame(x, y);
            bool frame_is_tile = frame.getTile() != nullptr;
            Robot *robot_on_frame = getRobotOnFrame(x, y);

            /* Top left corner of the frame --------------------------------- */
            temp_seperator += computeNode(board_to_display, x, y);

            /* Top wall ----------------------------------------------------- */

            /* No wall if it's the disabled frames in the middle */
            temp_seperator += this->boardTheme.reset_color;
            if (x == 7 && y == 8)
            {
                temp_seperator += "    ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += "   ";
            }
            /* Classic wall */
            else if (frame.getWalls()[UP])
            {
                temp_seperator += this->boardTheme.wall_color;
                temp_seperator += this->boardTheme.horizontal_wall;
            }
            /* No wall */
            else
            {
                temp_seperator += this->boardTheme.grid_color;
                temp_seperator += this->boardTheme.horizontal_grid;
            }
            temp_seperator += this->boardTheme.reset_color;

            /* Add right node if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                temp_seperator += computeNode(board_to_display, x + 1, y);
            }

            /* Left wall ---------------------------------------------------- */
            if ((x == 8 && y == 7) || (x == 8 && y == 8))
            {
                /* No walls in the middle of the board */
                temp_tiles += " ";
            }
            else if (frame.getWalls()[LEFT])
            {
                temp_tiles += this->boardTheme.wall_color;
                temp_tiles += this->boardTheme.vertical_wall;
            }
            else
            {
                temp_tiles += this->boardTheme.grid_color;
                temp_tiles += this->boardTheme.vertical_grid;
            }
            temp_seperator += this->boardTheme.reset_color;

            /* Tile content ------------------------------------------------- */

            /* Disabled tiles in the middle of the board */
            if ((x == 7 && y == 7) || (x == 8 && y == 7) || (x == 7 && y == 8) || (x == 8 && y == 8))
            {
                temp_tiles += EMPTY_FRAME;
            }
            else if ((frame_is_tile || robot_on_frame) && !show_empty)
            {
                /* Robot on the frame, and frame is a tile */
                if (frame_is_tile && robot_on_frame)
                {
                    temp_tiles += frame.getTile()->getEmoji();
                    temp_tiles += this->boardTheme.reset_color;
                    temp_tiles += robot_on_frame->getEmoji();
                }

                /* Robot on the frame */
                else if (robot_on_frame)
                {
                    temp_tiles += " " + robot_on_frame->getEmoji();
                    temp_tiles += this->boardTheme.reset_color + " ";
                }

                /* Frame is a tile */
                else if (frame_is_tile)
                {
                    temp_tiles += " " + frame.getTile()->getEmoji();
                    temp_tiles += this->boardTheme.reset_color + " ";
                }
            }
            else
            {
                /* Frame empty */
                temp_tiles += EMPTY_FRAME;
            }

            /* Add right wall if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                if (frame.getWalls()[RIGHT])
                {
                    temp_tiles += this->boardTheme.wall_color;
                    temp_tiles += this->boardTheme.vertical_wall;
                }
                else
                {
                    temp_tiles += this->boardTheme.grid_color;
                    temp_tiles += this->boardTheme.vertical_grid;
                }
                temp_seperator += this->boardTheme.reset_color;
            }
        }
        output += temp_seperator + ANSI_RESET + "\n" + this->boardTheme.reset_color;
        output += temp_tiles + ANSI_RESET + "\n" + this->boardTheme.reset_color;
    }

    /* Bottom border of the board */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = board_to_display.getFrame(x, BOARD_SIZE - 1);
        /* Node */
        temp_seperator += computeNode(board_to_display, x, BOARD_SIZE);

        /* Wall */
        if (frame.getWalls()[DOWN])
        {
            temp_seperator += this->boardTheme.wall_color;
            temp_seperator += this->boardTheme.horizontal_wall;
        }
        else
        {
            temp_seperator += this->boardTheme.grid_color;
            temp_seperator += this->boardTheme.horizontal_grid;
        }
        temp_seperator += this->boardTheme.reset_color;
    }

    /* Bottom right corner */
    temp_seperator += computeNode(board_to_display, BOARD_SIZE, BOARD_SIZE);

    output += temp_seperator + ANSI_RESET + "\n";

    /* Restore goal tile */
    if (show_empty)
    {
        this->goal_tile = save_goal_tile;
    }

    return output;
}

std::string GameManager::displayEmptyBoard()
{
    return this->displayBoard(true);
}

Robot *GameManager::getRobotOnFrame(int x, int y)
{
    for (Robot *robot : this->robots)
    {
        if (robot->getX() == x && robot->getY() == y)
        {
            return robot;
        }
    }
    return nullptr;
}

void GameManager::generateBoard()
{
    this->board.generate();

    if (!replace_robots_each_round)
    {
        // Place randomly robots on the board
        this->robots_coordinates.clear();
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            bool condition;
            do
            {
                x = rand() % 16;
                y = rand() % 16;
                condition = std::count(this->robots_coordinates.begin(), this->robots_coordinates.end(), std::make_pair(x, y)); // Coordinates already used
                // condition |= this->board.getFrame(x, y).getTile() == nullptr;                                                   // Frame not a tile
            } while (condition); // Vérifie si la position est déjà utilisée

            // Add coordinate
            this->robots_coordinates.push_back(std::make_pair(x, y));
        }
    }
}

void GameManager::setupRound()
{
    // Reset members
    this->round_finished = false;
    this->cur_player_won = false;
    this->moves_str = "";
    for (auto &&p : this->players)
    {
        p->resetMoves();
        p->incrementRoundsPlayed();
    }

    // Get the goal tile
    int goal_tile_index = rand() % Board::TILES.size();
    this->goal_tile = &Board::TILES[goal_tile_index];

    if (replace_robots_each_round)
    {
        // Place randomly robots on the board
        this->robots_coordinates.clear();
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            bool condition;
            do
            {
                x = rand() % 16;
                y = rand() % 16;
                condition = std::count(this->robots_coordinates.begin(), this->robots_coordinates.end(), std::make_pair(x, y)); // Coordinates already used
                // condition |= this->board.getFrame(x, y).getTile() == nullptr;                                                   // Frame not a tile
            } while (condition); // Vérifie si la position est déjà utilisée

            // Add coordinate
            this->robots_coordinates.push_back(std::make_pair(x, y));
        }
    }
}

void GameManager::resetRound()
{
    // Reset members
    this->round_finished = false;
    this->cur_player_won = false;
    this->moves_str = "";

    // Place robots on the board
    if (this->robots_coordinates.size() < 4)
        return;
    this->robots.clear();
    for (int i = 0; i < 4; i++)
    {
        int x = this->robots_coordinates[i].first;
        int y = this->robots_coordinates[i].second;
        this->robots.push_back(new Robot(Color(i), x, y));
    }
}

void GameManager::processPredictionsInputs()
{
    this->resetRound();

    Menu::clear();
    std::cout << this->displayBoard() << std::endl;
    std::cout << std::endl;
    std::cout << "When a player find a solution, press [ENTER] to send your predictions..." << std::endl;
    getchar(); // Wait ENTER pressed

    for (int i = 10; i > 0; i--)
    {
        Menu::clear();
        std::cout << this->displayBoard() << std::endl;
        std::cout << std::endl;
        std::cout << "\033[1mYou have \033[31m" << i << "\033[0m\033[1m seconds to find your solution prediction...\033[0m" << std::endl;
        sleep(1000);
    }

    Menu::clear();
    std::cin.clear();
    std::cout << this->displayEmptyBoard() << std::endl;

    for (auto &&player : this->players)
    {
        std::string prediction_str;
        std::cout << "Prediction for player " << player->getName() << ": " << std::flush;
        std::cin >> prediction_str;
        while (!is_number(prediction_str))
        {
            std::cout << "Prediction invalid! New prediction: " << std::flush;
            std::cin >> prediction_str;
        }
        int prediction = std::stoi(prediction_str);
        while (prediction < 2)
        {
            Menu::clear();
            std::cout << GAME_ASCII_BANNER << this->displayEmptyBoard() << std::endl;
            std::cout << "Your prediction must be greater than 1 ! " << std::endl;
            std::cout << ANSI_ITALIC ANSI_BLUE 
                         "Rules: \"If, after selecting a new objective tile, it turns out that the" << std::endl;
            std::cout << "        solution can be reached in a single move, players must ignore this" << std::endl;
            std::cout << "        solution and try to find another one.\"" ANSI_RESET << std::endl;
            std::cout << "New prediction: " << std::flush;
            std::cin >> prediction_str;
            while (!is_number(prediction_str))
            {
                std::cout << "Prediction invalid! New prediction: " << std::flush;
                std::cin >> prediction_str;
            }
        }
        player->setPrediction(prediction);
    }
}

void GameManager::sortPlayersByPredictions()
{
    std::sort(this->players.begin(), this->players.end(), [](Player *a, Player *b)
              { return a->getPrediction() < b->getPrediction(); });
}

void GameManager::sortPlayersByScore()
{
    std::sort(this->players.begin(), this->players.end(),
              [](Player *a, Player *b)
              { return a->getScore() > b->getScore(); });
}

bool GameManager::processMovement(Robot *robot, Direction direction, int *deplacement, Menu *m, int player_index)
{
    int robot_X = robot->getX();
    int robot_Y = robot->getY();

    bool robotNextTo = std::any_of(this->robots.begin(), this->robots.end(), [direction, robot_X, robot_Y](Robot *r)
                                   {
        bool result = false;
        switch (direction)
        {
        case UP:
            result = r->getX() == robot_X && r->getY() == robot_Y - 1;
            break;
        case DOWN:
            result = r->getX() == robot_X && r->getY() == robot_Y + 1;
            break;
        case LEFT:
            result = r->getX() == robot_X - 1 && r->getY() == robot_Y;
            break;
        case RIGHT:
            result = r->getX() == robot_X + 1 && r->getY() == robot_Y;
            break;
    
        default:
            break;
        }
        return result; });
    bool canMove = board.getFrame(robot_X, robot_Y).canMove(direction);
    int previousRobotX = robot_X;
    int previousRobotY = robot_Y;

    while (canMove && !robotNextTo && robot_X >= 0 && robot_X <= 15 && robot_Y >= 0 && robot_Y <= 15)
    {
        robot->move(direction);
        robot_X = robot->getX();
        robot_Y = robot->getY();
        robotNextTo = std::any_of(this->robots.begin(), this->robots.end(), [direction, robot_X, robot_Y](Robot *r)
                                  {
            bool result = false;
            switch (direction)
            {
            case UP:
                result = r->getX() == robot_X && r->getY() == robot_Y - 1;
                break;
            case DOWN:
                result = r->getX() == robot_X && r->getY() == robot_Y + 1;
                break;
            case LEFT:
                result = r->getX() == robot_X - 1 && r->getY() == robot_Y;
                break;
            case RIGHT:
                result = r->getX() == robot_X + 1 && r->getY() == robot_Y;
                break;
        
            default:
                break;
            }
            return result; });
        canMove = board.getFrame(robot_X, robot_Y).canMove(direction);
    }
    if (robot_X != previousRobotX || robot_Y != previousRobotY)
    {
        *deplacement += 1;
        this->players[player_index]->incrementMoves();
        this->moves_str += ANSI_BOLD;
        switch (robot->getColor())
        {
        case RED:
            this->moves_str += ANSI_RED;
            break;
        case GREEN:
            this->moves_str += ANSI_GREEN;
            break;
        case BLUE:
            this->moves_str += ANSI_BLUE;
            break;
        case YELLOW:
            this->moves_str += ANSI_YELLOW;
            break;
        default:
            break;
        }
        switch (direction)
        {
        case UP:
            this->moves_str += MOVE_ARROW_UP;
            break;
        case DOWN:
            this->moves_str += MOVE_ARROW_DOWN;
            break;
        case LEFT:
            this->moves_str += MOVE_ARROW_LEFT;
            break;
        case RIGHT:
            this->moves_str += MOVE_ARROW_RIGHT;
            break;
        default:
            break;
        }
        this->moves_str += ANSI_RESET;
    }
    m->setTitle(displayBoard() + this->players[player_index]->getName() + "'s moves: " + this->moves_str + "\n");
    m->displayMenu();

    if (this->board.getFrame(robot_X, robot_Y).getTile() == this->goal_tile &&
        (this->goal_tile->getColor() == robot->getColor() || this->goal_tile->getColor() == RAINBOW))
    {
        this->round_finished = true;
        this->cur_player_won = true;
        if (players[player_index]->getPrediction() == *deplacement)
            players[player_index]->incrementScore(2);
        else
            players[player_index]->incrementScore(1);
        this->roundWinner = this->players[player_index];
        return true;
    }

    if (*deplacement >= players[player_index]->getPrediction())
    {
        std::cout << "You have reached your prediction!" << std::endl;
        this->round_finished = true;
        this->cur_player_won = false;
        return true;
    }
    return false;
}

bool GameManager::playRound(int player_index)
{
    // Reset values
    int move_count = 0;
    this->resetRound();

    // Setup Menu
    Menu menu(displayBoard() + this->players[player_index]->getName() + " round\n", 0);
    menu.preventArguments(true);

    for (auto &&robot : this->robots)
    {
        std::string color;
        switch (robot->getColor())
        {
        case RED:
            color = "Red";
            break;
        case GREEN:
            color = "Green";
            break;
        case YELLOW:
            color = "Yellow";
            break;
        case BLUE:
            color = "Blue";
            break;

        default:
            break;
        }

        menu.addOption(color + " Robot", [&](int pos, Menu *m)
                       {

            // Setup Menu
            m->preventDeplacement(true);
            m->setColorSelection(this->boardTheme.menu_robot_selected_color);
            m->displayMenu();

            // Process movements
            char c = 0;
            std::cout << "Press 'ENTER' to unselect." << std::endl;
            while (c != '\r' && !this->round_finished)
            {
#ifdef _WIN32 // Windows sucks
                c = _getch();
                if (c == '\r' || c == 127) // enter or backspace
                    break;
                if (c == 224 || c == -32) // escape
                {
                    c = _getch();
                    switch (c)
                    {
                    case 72: // up arrow
                        if (this->processMovement(robot, UP, &move_count, m, player_index))
                            c = '\r';
                        break;
                    case 80: // down arrow
                        if (this->processMovement(robot, DOWN, &move_count, m, player_index))
                            c = '\r';
                        break;
                    case 77: // right arrow
                        if (this->processMovement(robot, RIGHT, &move_count, m, player_index))
                            c = '\r';
                        break;
                    case 75: // left arrow
                        if (this->processMovement(robot, LEFT, &move_count, m, player_index))
                            c = '\r';
                        break;
                    default:
                        break;
                    }
                }
#else
                c = getchar(); 
                if (c == '\r' || c == 127) // enter or backspace
                    break;
                if (c == 27) // escape
                {
                    c = getchar();
                    if (c == 91) // [
                    {
                        c = getchar();
                        switch (c)
                        {
                        case 65: // up arrow
                            if (this->processMovement(robot, UP, &move_count, m, player_index))
                                c = '\r';
                            break;
                        case 66: // down arrow
                            if (this->processMovement(robot, DOWN, &move_count, m, player_index))
                                c = '\r';
                            break;
                        case 67: // right arrow
                            if (this->processMovement(robot, RIGHT, &move_count, m, player_index))
                                c = '\r';
                            break;
                        case 68: // left arrow
                            if (this->processMovement(robot, LEFT, &move_count, m, player_index))
                                c = '\r';
                            break;
                        default: 
                            break;
                        }
                    }
                }
#endif
            }

            // Reset Menu
            m->preventDeplacement(false);
            m->preventArguments(false);
            m->setColorSelection(this->boardTheme.menu_selection_color);

            return !this->round_finished; });
    }

    menu.run();

    return this->cur_player_won;
}

std::string GameManager::displayRoundResults()
{
    std::string output = "\n";

    for (Player *player : this->players)
    {
        /* Get player info */
        std::string player_name = player->getName();
        std::string player_prediction = std::to_string(player->getPrediction());
        std::string player_moves = std::to_string(player->getNbMoves());
        std::string player_result;
        if (player == this->roundWinner)
        {
            player_result = ANSI_GREEN "won" ANSI_RESET " with " + player_moves + "!";
        }
        else
        {
            player_result = ANSI_RED "lost" ANSI_RESET;
        }

        /* Add player recap to output */
        output += "Player " ANSI_BOLD + player_name + ANSI_RESET_BOLD " announced " + player_prediction + " moves and " + player_result;
        output += "\n";
    }

    return output;
}

std::string GameManager::displayScoreboard()
{
    const std::string SPACE_BETWEEN_COLUMNS = "   ";

    std::vector<std::string> column_names = {"Rank", "Player", "Rounds played", "Score", "Success Rate"};
    int nb_columns = column_names.size();

    /*  Compute column widths depending on column names */
    std::vector<int> column_widths = {0, 0, 0, 0, 0};
    for (int i = 0; i < nb_columns; i++)
    {
        column_widths[i] = column_names[i].length();
    }

    /* Get the max length of the player names column */
    for (auto &&player : this->players)
    {
        if (((int)player->getName().length()) > column_widths[NAME_COLUMN])
        {
            column_widths[NAME_COLUMN] = player->getName().length();
        }
    }

    /* Sort players by score before displaying */
    sortPlayersByScore();

    /* Display top border of the frame -------------------------------------- */
    std::string output = "\n";

    /* Compute length of horizontal boarder */
    int scoreboard_width = std::accumulate(column_widths.begin(), column_widths.end(), 0);
    scoreboard_width += SPACE_BETWEEN_COLUMNS.length() * (nb_columns);
    std::string horizontal_border = "";
    for (int i = 0; i < (scoreboard_width); i++)
    {
        horizontal_border += HORIZONTAL_BORDER;
    }

    output += TOP_LEFT_CORNER;
    output += horizontal_border;
    output += TOP_RIGHT_CORNER "\n";

    /* Display first row ---------------------------------------------------- */
    output += VERTICAL_BORDER " ";
    output += ANSI_BOLD;
    for (int i = 0; i < nb_columns; i++)
    {
        output += column_names[i];
        output += SPACE_BETWEEN_COLUMNS;
        output += std::string(column_widths[i] - column_names[i].length(), ' ');
    }
    /* Remove SPACE_BETWEEN_COLUMN for the last column */
    output.pop_back();
    output.pop_back();
    output += ANSI_RESET;
    output += " " VERTICAL_BORDER "\n";

    /* Display others rows -------------------------------------------------- */
    bool show_podium = this->players.size() > 3;
    for (auto &&player : this->players)
    {
        /* Get player info */
        std::string player_rank;
        bool more_than_one_player = this->players.size() > 1;
        bool is_winner = (player == this->players[0]) && (this->players[0]->getScore() > 0);
        if (is_winner && more_than_one_player && !show_podium)
        {
            player_rank = "🏆";
        }
        else if (is_winner && show_podium)
        {
            player_rank = "🥇";
        }
        
        else if (player == this->players[1] && show_podium)
        {
            player_rank = "🥈";
        }
        else if (player == this->players[2] && show_podium)
        {
            player_rank = "🥉";
        }
        else
        {
            player_rank = " ";
            player_rank += std::to_string(std::find(this->players.begin(),
                                                    this->players.end(),
                                                    player) -
                                          this->players.begin() + 1);
        }
        std::string player_name = player->getName();
        std::string player_rounds = std::to_string(player->getRoundsPlayed());
        std::string player_score = std::to_string(player->getScore());
        std::string player_success_rate;
        if (player->getRoundsPlayed() == 0)
        {
            player_success_rate = "--";
        }
        else
        {
            int player_sucess_rate_int = (int)(((float)(player->getScore()) / (float)(player->getRoundsPlayed()) * 100) / 2);
            if (player_sucess_rate_int > 100)
            {
                player_sucess_rate_int = 100;
            }
            player_success_rate = std::to_string(player_sucess_rate_int) + "%";
        }

        /* Left border of frame */
        output += VERTICAL_BORDER " ";

        /* Player rank */
        output += player_rank;
        if (is_winner || show_podium)
        {
            /* std::string.lenght() throws error if string contains emoji  */
            output += std::string(column_widths[RANK_COLUMN] - 2, ' ');
        }
        else
        {
            output += std::string(column_widths[RANK_COLUMN] - player_rank.length(), ' ');
        }
        output += SPACE_BETWEEN_COLUMNS;

        /* Player name */
        output += player_name;
        output += std::string(column_widths[NAME_COLUMN] - player_name.length(), ' ');
        output += SPACE_BETWEEN_COLUMNS;

        /* Player rounds */
        output += player_rounds;
        output += std::string(column_widths[ROUNDS_COLUMN] - player_rounds.length(), ' ');
        output += SPACE_BETWEEN_COLUMNS;

        /* Player score  */
        output += player_score;
        output += std::string(column_widths[SCORE_COLUMN] - player_score.length(), ' ');
        output += SPACE_BETWEEN_COLUMNS;

        /* Player success rate  */
        output += player_success_rate;
        output += std::string(column_widths[SUCCESS_COLUMN] - player_success_rate.length(), ' ');

        /* Right border of frame */
        output += "  " VERTICAL_BORDER "\n";
    }

    /* Display bottom border of the frame ----------------------------------- */
    output += BOTTOM_LEFT_CORNER;
    output += horizontal_border;
    output += BOTTOM_RIGHT_CORNER;
    output += "\n";

    return output;
}