#include <iostream>

#include "MainMenuCallbacks.h"
#include "DisplayUtils.h"

bool MainMenu::CB_printHelp(int pos, Menu *m)
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
    std::cout << "    the puzzle with the correct prediction, he wins " red_word("2 points") "." << std::endl;
    std::cout << "    If he solves the puzzle with a lower number of moves than his " << std::endl;
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

Menu::MenuCallback_t MainMenu::play_CBBuilder(GameManager &gm)
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
            gm.setupRound();
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
                }
                CONTINUE_ON_ENTER_PROMPT
            } while (player_won == false && player_index < (int)gm.getPlayers().size());
        }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::addPlayer_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
        player_menu.setColorSelection(gm.getBoardTheme().menu_selection_color);
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
            bool found = false;
            for (auto &&player : gm.getPlayers())
            {
                if (player->getName() == player_name)
                {
                    found = true;
                    break;
                }
            }
            if (found) // Player name exists
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

Menu::MenuCallback_t MainMenu::removePlayer_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Remove Player\n" ANSI_RESET, 0);
        player_menu.setColorSelection(gm.getBoardTheme().menu_selection_color);
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

Menu::MenuCallback_t MainMenu::regenerateBoard_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.generateBoard();
        std::cout << "Done!" << std::endl;
        CONTINUE_ON_ENTER_PROMPT
        return true;
    };
    return lambda_cb;
}

bool MainMenu::CB_notImplementedYet(int pos, Menu *m)
{
    Menu::clear();
    std::cout << GAME_ASCII_BANNER << std::endl;
    std::cout << "Not emplemented yet! " << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return false;
}

Menu::MenuCallback_t MainMenu::settings_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu::clear();
        int position = 1;
        bool running = true;
        Menu settings_menu = Menu(GAME_ASCII_BANNER "Settings Menu")
                                 .preventArguments()
                                 .setColorSelection(gm.getBoardTheme().menu_selection_color)
                                 .addOption("Menu: Selection Color " + gm.getBoardTheme().menu_selection_color + "■" ANSI_RESET, SettingsMenu::menuSelectionColor_CBBuilder(gm))
                                 .addOption("Menu: Robot Selected Color " + gm.getBoardTheme().menu_robot_selected_color + "■" ANSI_RESET, SettingsMenu::menuRobotSelectedColor_CBBuilder(gm))
                                 .addOption(ANSI_ITALIC "Default." ANSI_RESET_ITALIC)
                                 .addOption(ANSI_ITALIC "Exit." ANSI_RESET_ITALIC, [&](int, Menu *)
                                            {running=false; return false; });

        while (running)
        {
            settings_menu.setOptionPos(position);
            position = settings_menu.run();
        }
        return false;
    };
    return lambda_cb;
}

// Menu::MenuCallback_t MainMenu::function_CBBuilder(GameManager &gm)
// {
//     auto lambda_cb = [&](int pos, Menu *m)
//     {
//         // some code

//         return false;
//     };
//     return lambda_cb;
// }

std::string MenuUtils::getColorWithMenu(std::string title, std::string selectionColor)
{
    std::string color = "";
    Menu colorMenu = Menu(title)
                         .setColorSelection(selectionColor)
                         .addOption("Black   " ANSI_BLACK "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BLACK; return false; })
                         .addOption("Red     " ANSI_RED "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_RED; return false; })
                         .addOption("Green   " ANSI_GREEN "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_GREEN; return false; })
                         .addOption("Yellow  " ANSI_YELLOW "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_YELLOW; return false; })
                         .addOption("Blue    " ANSI_BLUE "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BLUE; return false; })
                         .addOption("Magenta " ANSI_MAGENTA "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_MAGENTA; return false; })
                         .addOption("Cyan    " ANSI_CYAN "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_CYAN; return false; })
                         .addOption("White   " ANSI_WHITE "■" ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_WHITE; return false; });
    colorMenu.run();
    return color;
}

Menu::MenuCallback_t SettingsMenu::menuSelectionColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().menu_selection_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Menu Selection Color", gm.getBoardTheme().menu_selection_color);
        m->setColorSelection(gm.getBoardTheme().menu_selection_color);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::menuRobotSelectedColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().menu_robot_selected_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Menu Robot Selected Color", gm.getBoardTheme().menu_selection_color);
        return false;
    };
    return lambda_cb;
}