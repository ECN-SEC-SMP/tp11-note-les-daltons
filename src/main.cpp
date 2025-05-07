
#include <iostream>

#include "GameManager.h"
#include "Utils.h"

int main(int argc, char const *argv[])
{
    bool running = true;
    GameManager gm;
    gm.generateBoard();
    Menu main_menu = Menu("Main Menu", 0)
                         .addOption("Play")
                         .addOption("Add Player")
                         .addOption("Remove Player")
                         .addOption("Regenerate Board", [&](int pos, Menu *m)
                                    { gm.generateBoard(); std::cout << "Done!" << std::endl; sleep(3); return true; })
                         .addOption("Exit.", [&](int pos, Menu *m)
                                            { running = false; return false; });

    while (running)
    {
        Menu::clear();
        int pos = main_menu.run();
        if (!running) break;

        std::string player_name;
        switch (pos)
        {
        case 1: // Play
            if (gm.getPlayers().size() == 0)
            {
                std::cout << "No players added!" << std::endl;
                sleep(3);
                break;
            }
            gm.setupRound();
            gm.processPredictionsInputs();
            gm.sortPlayersByPredictions();
            gm.playRound(0);
            break;
        case 2: // Add Player
            std::cout << "Player name: " << std::flush;
            std::cin >> player_name;
            gm.addPlayer(new Player(player_name));
            std::cout << "Done!" << std::endl;
            break;
        
        default:
            break;
        }
    }

    // gm.addPlayer(new Player("Joueur 1"));
    // gm.addPlayer(new Player("Joueur 2"));
    // gm.addPlayer(new Player("Joueur 3"));

    // gm.setupRound();
    // gm.processPredictionsInputs();
    // gm.sortPlayersByPredictions();

    // gm.playRound(0);

    // std::cout << std::endl
    //           << "Press [ENTER] to quit..." << std::endl;
    // getchar();
    return 0;
}
