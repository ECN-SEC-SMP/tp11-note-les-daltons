#include <iostream>

#include "GameManager.h"
#include "DisplayUtils.h"
#include "Utils.h"

/* some stuff */
#define CONTINUE_ON_ENTER_PROMPT                              \
    std::cin.clear();                                         \
    std::cout << "Press [ENTER] to continue..." << std::endl; \
    getchar();
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

/* Prototypes */
std::string getPlayerList(std::vector<Player *> players);
bool CB_printHelp(int pos, Menu *m);
Menu::MenuCallback_t play_CBBuilder(GameManager &gm);
Menu::MenuCallback_t addPlayer_CBBuilder(GameManager &gm);
Menu::MenuCallback_t removePlayer_CBBuilder(GameManager &gm);
Menu::MenuCallback_t message_CBBuilder(std::string message);

/***************************************************************************
 *                              Main Function                              *
 ***************************************************************************/
int main(int argc, char const *argv[])
{
    bool running = true;
    GameManager gm;
    newRandomSeed();
    gm.generateBoard();
    Menu main_menu = Menu(GAME_ASCII_BANNER ANSI_BOLD "Main Menu" ANSI_RESET, 0)
                         .addOption("Play", play_CBBuilder(gm))
                         .addOption("Add Player", addPlayer_CBBuilder(gm))
                         .addOption("Remove Player", removePlayer_CBBuilder(gm))
                         .addOption("Regenerate Board", [&](int pos, Menu *m)
                                    { gm.generateBoard(); std::cout << "Done!" << std::endl; CONTINUE_ON_ENTER_PROMPT return true; })
                         .addOption("Stats", message_CBBuilder("Not emplemented yet! (Issue #22)"))    // Issue #22
                         .addOption("Settings", message_CBBuilder("Not emplemented yet! (Issue #26)")) // Issue #26
                         .addOption("Help", CB_printHelp)
                         .addOption("Exit.", [&](int pos, Menu *m)
                                    { running = false; return false; })
                         .preventArguments();

    int pos = 1;
    while (running)
    {
        main_menu.setTitle(GAME_ASCII_BANNER ANSI_BOLD "Main Menu\n\n" ANSI_RESET + getPlayerList(gm.getPlayers()));
        main_menu.setOptionPos(pos);
        pos = main_menu.run();
    }
    return 0;
}

/***************************************************************************
 *                          Additional Functions                           *
 ***************************************************************************/
/**
 * @brief Get the Player List for display
 *
 * @param players
 * @return std::string
 */
std::string getPlayerList(std::vector<Player *> players)
{
    std::string output = ANSI_BOLD ANSI_UNDERLINE "Players:" ANSI_RESET_BOLD ANSI_RESET_UNDERLINE "\n";
    if (players.size() == 0)
    {
        output += ANSI_ITALIC "No players...\n" ANSI_RESET_ITALIC;
    }
    for (auto &&player : players)
    {
        output += " > " + player->getName() + "\n";
    }
    output += ANSI_RESET;
    return output;
}

/***************************************************************************
 *                           Main Menu Callbacks                           *
 ***************************************************************************/
bool CB_printHelp(int pos, Menu *m)
{
    Menu::clear();

    std::cout << GAME_ASCII_BANNER;
    std::cout << ANSI_BOLD "Help Page" ANSI_RESET_BOLD << std::endl
              << std::endl;
    std::cout << ANSI_UNDERLINE "Rules:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " 1. The aim is to get the robot with the right color onto the" << std::endl;
    std::cout << "    tile corresponding to the tile in the center of the board." << std::endl;
    std::cout << " 2. At the start of the game, you must find a way to solve the" << std::endl;
    std::cout << "    puzzle with " ANSI_UNDERLINE "as few moves as possible." ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " 3. When someone has found their solution, they can press " << std::endl;
    std::cout << "    " key("[ENTER]") " and the other players must find their solution " << std::endl;
    std::cout << "    within " red_word("10 seconds") "." << std::endl;
    std::cout << " 4. After this time, all players enter their prediction of " << std::endl;
    std::cout << "    the number of moves." << std::endl;
    std::cout << " 5. The player with the lowest prediction starts. If he solves" << std::endl;
    std::cout << "    the puzzle with the correct prediction, he wins " red_word("2 points") ". If" << std::endl;
    std::cout << "    he solves the puzzle with a lower number of moves than his " << std::endl;
    std::cout << "    prediction, he earns only " red_word("1 point") "." << std::endl;
    std::cout << " 6. But if this player exceeds his prediction without solving" << std::endl;
    std::cout << "    the puzzle, the second player can play and continue from" << std::endl;
    std::cout << "    the previous rule." << std::endl;
    std::cout << std::endl;
    std::cout << ANSI_UNDERLINE "Game commands:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " To select a robot, use the arrow keys and press " key("[ENTER]") ". The" << std::endl;
    std::cout << " selected robot turns red. You can now use the arrow keys to" << std::endl;
    std::cout << " move the selected robot. To deselect a robot, press " key("[ENTER]") "" << std::endl;
    std::cout << " again. The selected robot turns green, and you can now move " << std::endl;
    std::cout << " the menu cursor." << std::endl;
    std::cout << ANSI_BLUE;
    std::cout << "                              [UP]" << std::endl;
    std::cout << "                     [LEFT] [ENTER] [RIGHT]" << std::endl;
    std::cout << "                             [DOWN]" << std::endl;
    std::cout << ANSI_RESET;
    std::cout << std::endl;
    std::cout << ANSI_UNDERLINE "Tile:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " Tiles are a combination of colors and shapes:" << std::endl
              << "   ";
    for (auto &&tile : Board::TILES)
        std::cout << tile.getEmoji() << " ";
    std::cout << std::endl;
    std::cout << " - The rainbow lets all the robots come to him" << std::endl;
    std::cout << "   to resole the puzzle." << std::endl;
    std::cout << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return true;
}

Menu::MenuCallback_t play_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        if (gm.getPlayers().size() == 0)
        {
            std::cout << "No players added!" << std::endl;
            CONTINUE_ON_ENTER_PROMPT
        }
        else
        {
            gm.setupNewRound();
            gm.processPredictionsInputs();
            gm.sortPlayersByPredictions();
            int player_index = 0;
            bool player_won = false;
            do
            {
                if ((player_won = gm.playRound(player_index)) == true)
                    std::cout << ANSI_GREEN ANSI_BOLD "You WON!!" ANSI_RESET << std::endl;
                else
                {
                    std::cout << ANSI_RED ANSI_BOLD "You Lose!" ANSI_RESET << std::endl;
                    player_index++;
                    if (player_index >= (int)gm.getPlayers().size())
                        break;
                }
                CONTINUE_ON_ENTER_PROMPT
            } while (player_won == false);
        }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t addPlayer_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
        player_menu.addOption("Player name: ").addOption("Cancel.");
        std::string player_name;
        int sel_pos;
        do
        {
            sel_pos = player_menu.run();
            if (sel_pos != 1)
                continue;
            player_name = player_menu.getOptionsArgs()[0];
        } while (player_name.empty() && sel_pos == 1);
        if (sel_pos == 1)
        {
#ifdef _WIN32
            // Windows sucks -> std::find_if NOT working ONLY on Windows !!!
            bool found = false;
            for (auto &&player : gm.getPlayers())
            {
                std::cout << "player->getName(): " << player->getName() << std::endl;
                std::cout << "player_name: " << player_name << std::endl;
                if (player->getName() == player_name)
                {
                    found = true;
                    break;
                }
            }

            if (found) // Player name exists
#else
            auto p = std::find_if(gm.getPlayers().begin(), gm.getPlayers().end(), [&](Player *p)
                                  { return p->getName() == player_name; });
            if (p != gm.getPlayers().end()) // Player name exists
#endif
            {
                std::cout << "This player name already exists! Retry." << std::endl;
                CONTINUE_ON_ENTER_PROMPT
            }
            else
                gm.addPlayer(new Player(player_name));
        }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t removePlayer_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Remove Player\n" ANSI_RESET, 0);
        player_menu.preventArguments();
        for (auto &&player : gm.getPlayers())
        {
            player_menu.addOption(player->getName());
        }
        player_menu.addOption("Cancel.");
        int player_pos = player_menu.run();
        if (player_pos > 0 && player_pos <= (int)gm.getPlayers().size())
        {
            gm.removePlayer(gm.getPlayers()[player_pos - 1]);
        }
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t message_CBBuilder(std::string message)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        std::cout << message << std::endl;
        CONTINUE_ON_ENTER_PROMPT

        return false;
    };
    return lambda_cb;
}

// Menu::MenuCallback_t function_CBBuilder(GameManager &gm)
// {
//     auto lambda_cb = [&](int pos, Menu *m)
//     {
//         // some code

//         return false;
//     };
//     return lambda_cb;
// }