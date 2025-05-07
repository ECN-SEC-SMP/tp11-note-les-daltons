#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include "typedef.h"
#include "GameManager.h"
#include "Menu.h"

#define RESET ANSI_RESET ANSI_WHITE_BG

/* Grid style */
#define GRID_COLOR ANSI_LIGHT_GRAY
#define HORIZONTAL_GRID GRID_COLOR "────" RESET
#define VERTICAL_GRID GRID_COLOR "│" RESET

/* Wall style */
#define WALL_COLOR ANSI_BLACK
#define HORIZONTAL_WALL WALL_COLOR "════" RESET
#define VERTICAL_WALL WALL_COLOR "║" RESET

/* Node styles */
#define NODE GRID_COLOR "┼" RESET
#define NODE_TOP WALL_COLOR "═" RESET
#define NODE_BOTTOM WALL_COLOR "═" RESET
#define NODE_LEFT WALL_COLOR "║" RESET
#define NODE_RIGHT WALL_COLOR "║" RESET
#define NODE_TOP_LEFT WALL_COLOR "╔" RESET
#define NODE_TOP_RIGHT WALL_COLOR "╗" RESET
#define NODE_BOTTOM_LEFT WALL_COLOR "╚" RESET
#define NODE_BOTTOM_RIGHT WALL_COLOR "╝" RESET

#define EMPTY_FRAME RESET "    "

/* Constructors */
GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{}

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

/* Methods */
void GameManager::addPlayer(Player *player)
{
    this->players.push_back(player);
}

void GameManager::removePlayer(Player *player)
{
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
}

void GameManager::generateBoard()
{
    this->board.generate();
}

std::string GameManager::displayBoard()
{
    int BOARD_SIZE = 16;

    std::string output = "\n" RESET;
    std::string temp_seperator = "";
    std::string temp_tiles = "";

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_seperator = "";
        temp_tiles = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame frame = this->board.getFrame(x, y);
            bool frame_is_tile = frame.getTile() != nullptr;
            Robot *robot_on_frame = getRobotOnFrame(x, y);

            /* Top left corner of the frame --------------------------------- */

            /* Goal tile displayed in the center of the board */
            if (x == 8 && y == 8)
            {
                temp_seperator += this->goal_tile->getEmoji();
            }
            /* Disabled frames in the middle */
            else if (x == 8 && y == 7)
            {
                temp_seperator += NODE_BOTTOM;
            }
            else if (x == 7 && y == 8)
            {
                temp_seperator += NODE_RIGHT;
            }
            else if (x == 9 && y == 8)
            {
                temp_seperator += NODE_LEFT;
            }
            else if (x == 8 && y == 9)
            {
                temp_seperator += NODE_TOP;
            }
            /* Top left corner */
            else if (x == 0 && y == 0)
            {
                temp_seperator += NODE_TOP_LEFT;
            }
            /* Left border */
            else if (x == 0)
            {
                temp_seperator += NODE_LEFT;
            }
            /* Top border */
            else if (y == 0)
            {
                temp_seperator += NODE_TOP;
            }
            /* Classic node */
            else
            {
                temp_seperator += NODE;
            }

            /* Top wall ----------------------------------------------------- */

            /* No wall if it's the disabled frames in the middle */
            if (x == 7 && y == 8)
            {
                temp_seperator += "    ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += RESET "   ";
            }
            /* Classic wall */
            else if (frame.getWalls()[UP])
            {
                temp_seperator += HORIZONTAL_WALL;
            }
            /* No wall */
            else
            {
                temp_seperator += HORIZONTAL_GRID;
            }

            /* Add right node if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                if (y == 0)
                {
                    temp_seperator += NODE_TOP_RIGHT;
                }
                else
                {
                    temp_seperator += NODE_RIGHT;
                }
            }

            /* Left wall ---------------------------------------------------- */
            if ((x == 8 && y == 7) || (x == 8 && y == 8))
            {
                /* No walls in the middle of the board */
                temp_tiles += " ";
            }
            else if (frame.getWalls()[LEFT])
            {
                temp_tiles += VERTICAL_WALL;
            }
            else
            {
                temp_tiles += VERTICAL_GRID;
            }

            /* Tile content ------------------------------------------------- */

            /* Disabled tiles in the middle of the board */
            if ((x == 7 && y == 7) || (x == 8 && y == 7) || (x == 7 && y == 8) || (x == 8 && y == 8))
            {
                temp_tiles += EMPTY_FRAME;
            }
            else if (frame_is_tile || robot_on_frame)
            {
                /* Robot on the frame, and frame is a tile */
                if (frame_is_tile && robot_on_frame)
                {
                    temp_tiles += frame.getTile()->getEmoji() + robot_on_frame->getEmoji();
                }

                /* Robot on the frame */
                else if (robot_on_frame)
                {
                    temp_tiles += " " + robot_on_frame->getEmoji() + " ";
                }

                /* Frame is a tile */
                else if (frame_is_tile)
                {
                    temp_tiles += " " + frame.getTile()->getEmoji() + " ";
                }
            }
            else
            {
                /* Frame empty */
                temp_tiles += EMPTY_FRAME;
            }

            /* TEMP ========================================================= */
            // if (frame.getWalls()[RIGHT])
            // {
            //     temp_tiles += VERTICAL_WALL;
            // }
            // else
            // {
            //     temp_tiles += VERTICAL_GRID;
            // }

            // if (frame.getWalls()[DOWN])
            // {
            //     temp_seperator += HORIZONTAL_WALL;
            // }
            // else
            // {
            //     temp_seperator += HORIZONTAL_GRID;
            // }

            /* ============================================================== */

            /* Add right wall if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                if (frame.getWalls()[RIGHT])
                {
                    temp_tiles += VERTICAL_WALL;
                }
                else
                {
                    temp_tiles += VERTICAL_GRID;
                }
            }
        }
        output += temp_seperator + ANSI_RESET + "\n" + RESET;
        output += temp_tiles + ANSI_RESET + "\n" + RESET;
    }

    /* Last row */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = this->board.getFrame(x, BOARD_SIZE - 1);
        /* Node */
        if (x == 0)
        {
            temp_seperator += NODE_BOTTOM_LEFT;
        }
        else
        {
            temp_seperator += NODE_BOTTOM;
        }

        /* Wall */
        if (frame.getWalls()[DOWN])
        {
            temp_seperator += HORIZONTAL_WALL;
        }
        else
        {
            temp_seperator += HORIZONTAL_GRID;
        }
    }

    /* Bottom right corner */
    temp_seperator += NODE_BOTTOM_RIGHT;

    output += temp_seperator + ANSI_RESET + "\n";

    return output;
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

void GameManager::setupRound()
{
    // Get the goal tile
    int goal_tile_index = rand() % Board::TILES.size();
    this->goal_tile = &Board::TILES[goal_tile_index];

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

        this->robots.push_back(new Robot(Color(i), x, y));
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
        std::cout << "\033[1mYou have \033[31m" << i << "\033[0m\033[1m seconds to find your solution prdiction...\033[0m" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    Menu::clear();
    std::cin.clear();

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
        player->setPrediction(std::stoi(prediction_str));
    }
}

void GameManager::sortPlayersByPredictions()
{
    std::sort(this->players.begin(), this->players.end(), [](Player* a, Player* b)
              { return a->getPrediction() < b->getPrediction(); });

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
    }
    m->setTitle(displayBoard());
    m->displayMenu();

    if (this->board.getFrame(robot_X, robot_Y).getTile() == this->goal_tile && this->goal_tile->getColor() == robot->getColor())
    {
        std::cout << "\033[32m\033[1m You won !!\033[0m" << std::endl;
        this->round_finished = true;
        this->cur_player_won = true;
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
    int move_count = 0;
    Menu menu(displayBoard(), 0);
    menu.preventArguments(true);
    this->cur_player_won = false;

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
            m->setColorSelection(31);
            m->displayMenu();

            // Process movements
            char c = 0;
            std::cout << "Press 'ENTER' to unselect." << std::endl;
            while (c != '\r' && !this->round_finished)
            {
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
            }

            // Reset Menu
            m->preventDeplacement(false);
            m->preventArguments(false);
            m->setColorSelection(32);

            return !this->round_finished;
        });
    }

    menu.run();

    return this->cur_player_won;
}
