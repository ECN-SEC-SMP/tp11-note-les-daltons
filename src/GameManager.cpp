#include <stdexcept>
#include <algorithm>
#include "GameManager.h"

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
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

Robot *GameManager::getRobot(Color color)
{
    auto it = std::find_if(this->robots.begin(), this->robots.end(), [color](Robot *robot)
                           { return robot->getColor() == color; });
    if (it != this->robots.end())
        return *it;
    else
        return nullptr;
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

std::string GameManager::displayBoard()
{
    // Temporary implementation to avoid compile error
    return "Board display not implemented yet.";
}
// {
//     /* TODO: prévoir les 4 tiles éteintes au centre du plateau */

//     std::string output = "";
//     std::string temp_seperator = "+----+----+----+----+----+----+----+----+\n";
//     std::string temp_tiles = "";
//     for (int x = 0; x < 16; x++)
//     {
//         for (int y = 0; y < 16; y++)
//         {
//             Frame frame = this->board.getFrame(x, y);
//             /* Top wall */
//             if (frame.getWalls()[UP])
//             {
//                 temp_seperator += "+----";
//             }
//             else
//             {
//                 temp_seperator += "+    ";
//             }

//             /* Left wall */
//             if (frame.getWalls()[LEFT])
//             {
//                 temp_tiles += "| ";
//             }
//             else
//             {
//                 temp_tiles += "  ";
//             }

//             /* Tile content */
//             if (frame.getTile() != nullptr)
//             {
//                 /* Tile not empty */
//                 Color frame_tile_color = frame.getTile()->getColor();
//                 Shape frame_tile_shape = frame.getTile()->getShape();
//                 temp_tiles += "X";
//             }
//             else
//             {
//                 /* Tile empty */
//                 temp_tiles += " ";
//             }

//             /* Check if it's the last tile of the row */
//             if (y == 15)
//             {
//                 temp_tiles += "|";
//             }
//         }
//         output += temp_seperator + "\n";
//         output += temp_tiles + "\n";
//     }
//     /* Bottom wall */
//     output += "+----+----+----+----+----+----+----+----+";

//     return output;
// }

void GameManager::playRound(int player_index)
{
    int deplacement = 0;

    Menu menu(displayBoard(), 1);

    for (size_t i = 0; i < robots.size(); i++)
    {
        int robot_X = robots[i]->getX();
        int robot_Y = robots[i]->getY();

        menu.addOption("Robot " + std::to_string(robots[i]->getColor()), [&](int, Menu *m)
                       {
            m->preventDeplacement(true);
            m->preventArguments(true);
            m->setColorSelection(31);
            m->displayMenu();
            // Menu::resetTerminal();
            char c = 0;
            std::cout << "Press 'ENTER' to unselect." << std::endl;
            while (c != '\r')
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
                        {
                            bool robotAbove = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                return r->getX() == robot_X && r->getY() == robot_Y - 1;
                            });
                            bool canMoveUp = board.getFrame(robot_X, robot_Y).canMove(UP);
                            int previousRobotY = robot_Y;
                            while(canMoveUp && !robotAbove)
                            {   
                                robots[i]->move(UP);
                                robotAbove = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                    return r->getX() == robot_X && r->getY() == robot_Y - 1;});
                                canMoveUp = board.getFrame(robot_X, robot_Y).canMove(UP);
                            }
                            if (robot_Y != previousRobotY)
                            {
                                deplacement += 1;
                            }
                            m->setTitle(displayBoard());
                            m->displayMenu();
                            if(deplacement >= players[player_index]->getPrediction())
                            {
                                std::cout << "You have reached your prediction!" << std::endl;
                                m->preventDeplacement(false);
                                m->preventArguments(false);
                                m->setColorSelection(32);
                                return true;
                            }
                            break;
                        }
                        case 66: // down arrow
                        {
                            bool robotBelow = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                return r->getX() == robot_X && r->getY() == robot_Y + 1;});
                            bool canMoveDown = board.getFrame(robot_X, robot_Y).canMove(DOWN);
                            int previousRobotY = robot_Y;
                            while(canMoveDown && !robotBelow)
                            {
                                robots[i]->move(DOWN);
                                robotBelow = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                    return r->getX() == robot_X && r->getY() == robot_Y + 1;});
                                canMoveDown = board.getFrame(robot_X, robot_Y).canMove(DOWN);
                            }
                            if (robot_Y != previousRobotY)
                            {
                                deplacement += 1;
                            }
                            m->setTitle(displayBoard());
                            m->displayMenu();
                            if(deplacement >= players[player_index]->getPrediction())
                            {
                                std::cout << "You have reached your prediction!" << std::endl;
                                m->preventDeplacement(false);
                                m->preventArguments(false);
                                m->setColorSelection(32);
                                return true;
                            }
                            break;
                        }
                        case 67: // right arrow
                        {
                            bool robotRight = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                return r->getX() == robot_X + 1 && r->getY() == robot_Y;});
                            bool canMoveRight = board.getFrame(robot_X, robot_Y).canMove(RIGHT);
                            int previousRobotX = robot_X;
                            while(canMoveRight && !robotRight)
                            {
                                robots[i]->move(RIGHT);
                                robotRight = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                    return r->getX() == robot_X + 1 && r->getY() == robot_Y;});
                                canMoveRight = board.getFrame(robot_X, robot_Y).canMove(RIGHT);
                            }
                            if (robot_X != previousRobotX)
                            {
                                deplacement += 1;
                            }
                            m->setTitle(displayBoard());
                            m->displayMenu();
                            if(deplacement >= players[player_index]->getPrediction())
                            {
                                std::cout << "You have reached your prediction!" << std::endl;
                                m->preventDeplacement(false);
                                m->preventArguments(false);
                                m->setColorSelection(32);
                                return true;
                            }
                            break;
                        }
                        case 68: // left arrow
                        {
                            bool robotLeft = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                return r->getX() == robot_X - 1 && r->getY() == robot_Y;});
                            bool canMoveLeft = board.getFrame(robot_X, robot_Y).canMove(LEFT);
                            int previousRobotX = robot_X;
                            while(canMoveLeft && !robotLeft)
                            {
                                robots[i]->move(LEFT);
                                robotLeft = std::any_of(robots.begin(), robots.end(), [robot_X, robot_Y](Robot *r) {
                                    return r->getX() == robot_X - 1 && r->getY() == robot_Y;});
                                canMoveLeft = board.getFrame(robot_X, robot_Y).canMove(LEFT);
                            }
                            if (robot_X != previousRobotX)
                            {
                                deplacement += 1;
                            }
                            m->setTitle(displayBoard());
                            m->displayMenu();
                            if (deplacement >= players[player_index]->getPrediction())
                            {
                                std::cout << "You have reached your prediction!" << std::endl;
                                m->preventDeplacement(false);
                                m->preventArguments(false);
                                m->setColorSelection(32);
                                return true;
                            }
                            break;
                        }
                        }
                    }
                }
            }
            // Menu::setTerminal();
            m->preventDeplacement(false);
            m->preventArguments(false);
            m->setColorSelection(32);
            return true; });
    }
    int result = menu.run();

    std::cout << "You selected option " << result << std::endl;
    std::cout << "Arguments: " << std::endl;
    for (const auto &arg : menu.getOptionsArgs())
    {
        std::cout << arg << std::endl;
    }
}
