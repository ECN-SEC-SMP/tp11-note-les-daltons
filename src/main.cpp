
#include <iostream>

#include "GameManager.h"
#include "Utils.h"

#define CONTINUE_ON_ENTER_PROMPT                              \
    std::cin.clear();                                         \
    std::cout << "Press [ENTER] to continue..." << std::endl; \
    getchar();

int main(int argc, char const *argv[])
{
    bool running = true;
    GameManager gm;
    gm.generateBoard();
    Menu main_menu = Menu(GAME_ASCII_BANNER ANSI_BOLD "Main Menu" ANSI_RESET, 0)
                         .addOption("Play")
                         .addOption("Add Player")
                         .addOption("Remove Player")
                         .addOption("Regenerate Board", [&](int pos, Menu *m)
                                    { gm.generateBoard(); std::cout << "Done!" << std::endl; CONTINUE_ON_ENTER_PROMPT return true; })
                         .addOption("Exit.", [&](int pos, Menu *m)
                                    { running = false; return false; })
                         .preventArguments();

    while (running)
    {
        Menu::clear();
        int pos = main_menu.run();
        if (!running)
            break;
        if (pos == 1) // Play
        {
            if (gm.getPlayers().size() == 0)
            {
                std::cout << "No players added!" << std::endl;
                CONTINUE_ON_ENTER_PROMPT
                continue;
            }
            gm.setupRound();
            gm.processPredictionsInputs();
            gm.sortPlayersByPredictions();
            if (gm.playRound(0))
                std::cout << ANSI_GREEN ANSI_BOLD "You WON!!" ANSI_RESET << std::endl;
            else
                std::cout << ANSI_RED ANSI_BOLD "You Lose!" ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
        }
        else if (pos == 2) // Add Player
        {
            Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
            player_menu.addOption("Player name: ").addOption("Cancel.");
            int sel_pos = player_menu.run();
            if (sel_pos != 1) continue;
            std::string player_name = player_menu.getOptionsArgs()[0];
            gm.addPlayer(new Player(player_name));
        }
        else if (pos == 3) // Remove Player
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
                std::cout << "Done!" << std::endl;
                CONTINUE_ON_ENTER_PROMPT
            }
        }
    }
    return 0;
}
