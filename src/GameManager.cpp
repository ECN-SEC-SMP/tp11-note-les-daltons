#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "GameManager.h"
#include "typedef.h"

/* Grid style */
#define GRID_COLOR "\033[38;5;245m"
#define HORIZONTAL_GRID GRID_COLOR "────" ANSI_RESET
#define VERTICAL_GRID GRID_COLOR "│" ANSI_RESET

/* Wall style */
#define WALL_COLOR ANSI_WHITE
#define HORIZONTAL_WALL WALL_COLOR "════" ANSI_RESET
#define VERTICAL_WALL WALL_COLOR "║" ANSI_RESET

/* Node styles */
#define NODE GRID_COLOR "┼" ANSI_RESET
#define NODE_TOP GRID_COLOR "┬" ANSI_RESET
#define NODE_BOTTOM GRID_COLOR "┴" ANSI_RESET
#define NODE_LEFT GRID_COLOR "├" ANSI_RESET
#define NODE_RIGHT GRID_COLOR "┤" ANSI_RESET
#define NODE_TOP_LEFT GRID_COLOR "┌" ANSI_RESET
#define NODE_TOP_RIGHT GRID_COLOR "┐" ANSI_RESET
#define NODE_BOTTOM_LEFT GRID_COLOR "└" ANSI_RESET
#define NODE_BOTTOM_RIGHT GRID_COLOR "┘" ANSI_RESET

#define DISABLED " " // for disabled frames in the middle of the board

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
}

GameManager::~GameManager()
{
    delete this->goal_tile;
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

/* Methods */

void GameManager::addPlayer(Player *player)
{
    this->players.push_back(player);
}

void GameManager::removePlayer(Player *player)
{
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
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

std::string GameManager::displayBoard()
{
    int BOARD_SIZE = 16;

    std::string output = "\n";
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
                temp_seperator += "X";//this->goal_tile->getEmoji();
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
                temp_seperator += " " DISABLED DISABLED " ";
            }
            else if (x == 8 && y == 8)
            {
                temp_seperator += " " DISABLED DISABLED " ";
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
                temp_tiles += DISABLED;
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
            if (x == 7 && y == 7)
            {
                temp_tiles += DISABLED DISABLED DISABLED DISABLED;
            }
            else if (x == 8 && y == 8)
            {
                temp_tiles += DISABLED DISABLED DISABLED " ";
            }
            else if (x == 7 && y == 8)
            {
                temp_tiles += DISABLED DISABLED DISABLED DISABLED;
            }
            else if (x == 8 && y == 7)
            {
                temp_tiles += DISABLED DISABLED DISABLED " ";
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
                /* Tile empty */
                temp_tiles += "    ";
            }

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
        output += temp_seperator + "\n";
        output += temp_tiles + "\n";
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

    output += temp_seperator + "\n";

    return output;
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
    ///////////////////////////////
    this->robots.push_back(new Robot(RED, std::pair<int, int>(random() % 16, random() % 16)));
    this->robots.push_back(new Robot(BLUE, std::pair<int, int>(random() % 16, random() % 16)));
    this->robots.push_back(new Robot(GREEN, std::pair<int, int>(random() % 16, random() % 16)));
    this->robots.push_back(new Robot(YELLOW, std::pair<int, int>(random() % 16, random() % 16)));
    for (auto &&p : this->players)
    {
        p->setPrediction(100);
    }
    this->goal_tile = new Tile(RED, TRIANGLE);
    this->board.generate();
    ///////////////////////////////

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

// void GameManager::playRound(int player_index)
// {
//     int deplacement = 0;

//     Menu menu(displayBoard(), 1);

//     for (size_t i = 0; i < robots.size(); i++)
//     {
//         int robot_X = robots[i]->getX();
//         int robot_Y = robots[i]->getY();

//         menu.addOption("Robot " + std::to_string(robots[i]->getColor()), [&](int, Menu *m)
//                        {
//             m->preventDeplacement(true);
//             m->preventArguments(true);
//             m->setColorSelection(31);
//             m->displayMenu();
//             // Menu::resetTerminal();
//             char c = 0;
//             std::cout << "Press 'ENTER' to unselect." << std::endl;
//             while (c != '\r')
//             {
//                 c = getchar(); 
//                 if (c == '\r' || c == 127) // enter or backspace
//                     break;
//                 if (c == 27) // escape
//                 {
//                     c = getchar();
//                     if (c == 91) // [
//                     {
//                         c = getchar();
//                         switch (c)
//                         {
//                         case 65: // up arrow
//                         {
//                             bool robotAbove = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                 return r->getX() == robot_X && r->getY() == robot_Y - 1;
//                             });
//                             bool canMoveUp = board.getFrame(robot_X, robot_Y).canMove(UP);
//                             int previousRobotY = robot_Y;
//                             while(canMoveUp && !robotAbove)
//                             {   
//                                 robots[i]->move(UP);
//                                 robotAbove = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                     return r->getX() == robot_X && r->getY() == robot_Y - 1;});
//                                 canMoveUp = board.getFrame(robot_X, robot_Y).canMove(UP);
//                             }
//                             if (robot_Y != previousRobotY)
//                             {
//                                 deplacement += 1;
//                             }
//                             m->setTitle(displayBoard());
//                             m->displayMenu();
//                             if(deplacement >= players[player_index]->getPrediction())
//                             {
//                                 std::cout << "You have reached your prediction!" << std::endl;
//                                 m->preventDeplacement(false);
//                                 m->preventArguments(false);
//                                 m->setColorSelection(32);
//                                 return true;
//                             }
//                             break;
//                         }
//                         case 66: // down arrow
//                         {
//                             bool robotBelow = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                 return r->getX() == robot_X && r->getY() == robot_Y + 1;});
//                             bool canMoveDown = board.getFrame(robot_X, robot_Y).canMove(DOWN);
//                             int previousRobotY = robot_Y;
//                             while(canMoveDown && !robotBelow)
//                             {
//                                 robots[i]->move(DOWN);
//                                 robotBelow = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                     return r->getX() == robot_X && r->getY() == robot_Y + 1;});
//                                 canMoveDown = board.getFrame(robot_X, robot_Y).canMove(DOWN);
//                             }
//                             if (robot_Y != previousRobotY)
//                             {
//                                 deplacement += 1;
//                             }
//                             m->setTitle(displayBoard());
//                             m->displayMenu();
//                             if(deplacement >= players[player_index]->getPrediction())
//                             {
//                                 std::cout << "You have reached your prediction!" << std::endl;
//                                 m->preventDeplacement(false);
//                                 m->preventArguments(false);
//                                 m->setColorSelection(32);
//                                 return true;
//                             }
//                             break;
//                         }
//                         case 67: // right arrow
//                         {
//                             bool robotRight = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                 return r->getX() == robot_X + 1 && r->getY() == robot_Y;});
//                             bool canMoveRight = board.getFrame(robot_X, robot_Y).canMove(RIGHT);
//                             int previousRobotX = robot_X;
//                             while(canMoveRight && !robotRight)
//                             {
//                                 robots[i]->move(RIGHT);
//                                 robotRight = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                     return r->getX() == robot_X + 1 && r->getY() == robot_Y;});
//                                 canMoveRight = board.getFrame(robot_X, robot_Y).canMove(RIGHT);
//                             }
//                             if (robot_X != previousRobotX)
//                             {
//                                 deplacement += 1;
//                             }
//                             m->setTitle(displayBoard());
//                             m->displayMenu();
//                             if(deplacement >= players[player_index]->getPrediction())
//                             {
//                                 std::cout << "You have reached your prediction!" << std::endl;
//                                 m->preventDeplacement(false);
//                                 m->preventArguments(false);
//                                 m->setColorSelection(32);
//                                 return true;
//                             }
//                             break;
//                         }
//                         case 68: // left arrow
//                         {
//                             bool robotLeft = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                 return r->getX() == robot_X - 1 && r->getY() == robot_Y;});
//                             bool canMoveLeft = board.getFrame(robot_X, robot_Y).canMove(LEFT);
//                             int previousRobotX = robot_X;
//                             while(canMoveLeft && !robotLeft)
//                             {
//                                 robots[i]->move(LEFT);
//                                 robotLeft = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
//                                     return r->getX() == robot_X - 1 && r->getY() == robot_Y;});
//                                 canMoveLeft = board.getFrame(robot_X, robot_Y).canMove(LEFT);
//                             }
//                             if (robot_X != previousRobotX)
//                             {
//                                 deplacement += 1;
//                             }
//                             m->setTitle(displayBoard());
//                             m->displayMenu();
//                             if (deplacement >= players[player_index]->getPrediction())
//                             {
//                                 std::cout << "You have reached your prediction!" << std::endl;
//                                 m->preventDeplacement(false);
//                                 m->preventArguments(false);
//                                 m->setColorSelection(32);
//                                 return true;
//                             }
//                             break;
//                         }
//                         }
//                     }
//                 }
//             }
//             // Menu::setTerminal();
//             m->preventDeplacement(false);
//             m->preventArguments(false);
//             m->setColorSelection(32);
//             return true; });
//     }
//     int result = menu.run();

//     std::cout << "You selected option " << result << std::endl;
//     std::cout << "Arguments: " << std::endl;
//     for (const auto &arg : menu.getOptionsArgs())
//     {
//         std::cout << arg << std::endl;
//     }
// }
