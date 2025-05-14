#include <iostream>

#include "GameManager.h"
#include "DisplayUtils.h"
#include "Utils.h"
#include "MainMenuCallbacks.h"

/* Prototypes*/
std::string getPlayerList(std::vector<Player *> players);

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
                         .setColorSelection(gm.getBoardTheme().menu_selection_color)
                         .addOption("Play", MainMenu::play_CBBuilder(gm))
                         .addOption("Add Player", MainMenu::addPlayer_CBBuilder(gm))
                         .addOption("Remove Player", MainMenu::removePlayer_CBBuilder(gm))
                         .addOption("Regenerate Board", MainMenu::regenerateBoard_CBBuilder(gm))
                         .addOption("Stats", MainMenu::stats_CBBuilder(gm))
                         .addOption("Settings", MainMenu::settings_CBBuilder(gm))
                         .addOption("Help", MainMenu::CB_printHelp)
                         .addOption("Exit.", [&](int pos, Menu *m)
                                    { running = false; return false; })
                         .preventArguments();

    int pos = 1;
    while (running)
    {
        main_menu.setTitle(GAME_ASCII_BANNER ANSI_BOLD "Main Menu\n\n" ANSI_RESET + getPlayerList(gm.getPlayers())); // Actualize title
        main_menu.setOptionPos(pos);                                                                                 // Keep last position
        main_menu.setColorSelection(gm.getBoardTheme().menu_selection_color);                                        // Update section color
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