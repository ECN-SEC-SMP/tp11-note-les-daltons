#include <stdexcept>
#include <algorithm>

#include "typedef.h"
#include "GameManager.h"

#define BOARD_SIZE 16

/* Constructors */

GameManager::GameManager()
    : goal_tile(nullptr), board(Board()), players(std::vector<Player *>())
{
    this->setWallsStyle(SIMPLE_WALLS);
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

/* Setters */

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
} 

// void GameManager::setColorTheme(ColorTheme colorTheme)
// {
//     switch (colorTheme)
//     {
//     case LIGHT_THEME:
//         this->boardTheme.background_color = ANSI_WHITE_BG;
//         this->boardTheme.grid_color = ANSI_LIGHT_GRAY;
//         this->boardTheme.wall_color = ANSI_BLACK;
//         break;

//     case DARK_THEME:
//         this->boardTheme.background_color = ANSI_BLACK;
//         this->boardTheme.grid_color = ANSI_LIGHT_GRAY;
//         this->boardTheme.wall_color = ANSI_WHITE_BG;
//         break;
//     }
// }

/* Methods */

void GameManager::addPlayer(Player *player)
{
    this->players.push_back(player);
}

void GameManager::removePlayer(Player *player)
{
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
}

std::string GameManager::computeNode(int x, int y)
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
    Frame current_frame = this->board.getFrame(x, y);
    Frame left_frame = this->board.getFrame(x - 1, y);
    Frame top_left_frame = this->board.getFrame(x - 1, y - 1);
    Frame top_frame = this->board.getFrame(x, y - 1);

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

    std::string node;
    /* Goal tile displayed in the center of the board */
    if (x == 8 && y == 8)
    {
        if (this->goal_tile == nullptr)
        {
            throw std::runtime_error("Goal tile is not set");
        }
        node = this->goal_tile->getEmoji();
    }
    else
    {
        if (top_wall && left_wall && bottom_wall && right_wall)
        {
            node = this->boardTheme.node_middle;
        }

        /* Walls */
        else if (left_wall && right_wall && !top_wall && !bottom_wall) 
        {
            node = this->boardTheme.node_horizontal;
        }
        else if (top_wall && bottom_wall && !left_wall && !right_wall) 
        {
            node = this->boardTheme.node_vertical;
        }

        /* Corners */
        else if (bottom_wall && right_wall && !top_wall && !left_wall)
        {
            node = this->boardTheme.node_top_left;
        }
        else if (left_wall && bottom_wall && !top_wall && !right_wall)
        {
            node = this->boardTheme.node_top_right;
        }
        else if (top_wall && left_wall && !bottom_wall && !right_wall)
        {
            node = this->boardTheme.node_bottom_right;
        }
        else if (top_wall && right_wall && !bottom_wall && !left_wall)
        {
            node = this->boardTheme.node_bottom_left;
        }
        
        /* Node with 3 walls */
        else if (left_wall && bottom_wall && right_wall && !top_wall)
        {
            node = this->boardTheme.node_top;
        }
        else if (left_wall && top_wall && right_wall && !bottom_wall)
        {
            node = this->boardTheme.node_bottom;
        }
        else if (top_wall && right_wall && bottom_wall && !left_wall)
        {
            node = this->boardTheme.node_left;
        }
        else if (top_wall && left_wall && bottom_wall && !right_wall)
        {
            node = this->boardTheme.node_right;
        }

        /* Grid node */
        else
        {
            node += this->boardTheme.node;
        }
    }

    return node;
}

std::string GameManager::displayBoard()
{
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
            temp_seperator += computeNode(x, y);

            /* Top wall ----------------------------------------------------- */

            /* No wall if it's the disabled frames in the middle */
            temp_seperator += RESET;
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
                temp_seperator += this->boardTheme.horizontal_wall;
            }
            /* No wall */
            else
            {
                temp_seperator += this->boardTheme.horizontal_grid;
            }

            /* Add right node if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                temp_seperator += computeNode(x + 1, y);
            }

            /* Left wall ---------------------------------------------------- */
            if ((x == 8 && y == 7) || (x == 8 && y == 8))
            {
                /* No walls in the middle of the board */
                temp_tiles += " ";
            }
            else if (frame.getWalls()[LEFT])
            {
                temp_tiles += this->boardTheme.vertical_wall;
            }
            else
            {
                temp_tiles += this->boardTheme.vertical_grid;
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

            /* Add right wall if it's the last column */
            if (x == BOARD_SIZE - 1)
            {
                if (frame.getWalls()[RIGHT])
                {
                    temp_tiles += this->boardTheme.vertical_wall;
                }
                else
                {
                    temp_tiles += this->boardTheme.vertical_grid;
                }
            }
        }
        output += temp_seperator + ANSI_RESET + "\n" + RESET;
        output += temp_tiles + ANSI_RESET + "\n" + RESET;
    }

    /* Bottom border of the board */
    temp_seperator = "";
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        Frame frame = this->board.getFrame(x, BOARD_SIZE - 1);
        /* Node */
        temp_seperator += computeNode(x, BOARD_SIZE);

        /* Wall */
        if (frame.getWalls()[DOWN])
        {
            temp_seperator += this->boardTheme.horizontal_wall;
        }
        else
        {
            temp_seperator += this->boardTheme.horizontal_grid;
        }
    }

    /* Bottom right corner */
    temp_seperator += computeNode(BOARD_SIZE, BOARD_SIZE);

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

void GameManager::generateBoard()
{
    this->board.generate();
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
    std::sort(this->players.begin(), this->players.end(), [](Player *a, Player *b)
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

            return !this->round_finished; });
    }

    menu.run();

    return this->cur_player_won;
}
