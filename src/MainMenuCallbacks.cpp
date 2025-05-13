#include <iostream>

#include "MainMenuCallbacks.h"
#include "DisplayUtils.h"

#define COLOR_DEMONSTRATION_CHAR "■"
#define BG_COLOR_DEMONSTRATION_CHAR "  "

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
            Menu::clear();
            std::cout << gm.displayBoard() << gm.displayRoundResults() << std::endl;
            CONTINUE_ON_ENTER_PROMPT
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
        gm.resetRound();
        Menu menu = Menu(gm.displayBoard()).addOption("Regenerate").addOption("Exit.").preventArguments();
        int _pos = 1;
        while (_pos != 2)
        {
            _pos = menu.run();
            gm.generateBoard();
            if (!gm.robotsAreReplacedEachRound())
                gm.resetRound();
            menu.setTitle(gm.displayBoard());
        }
        return false;
    };
    return lambda_cb;
}

bool MainMenu::CB_notImplementedYet(int pos, Menu *m)
{
    Menu::clear();
    std::cout << GAME_ASCII_BANNER << std::endl;
    std::cout << "Not implemented yet! " << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return false;
}

Menu::MenuCallback_t MainMenu::stats_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu stats_menu = Menu(GAME_ASCII_BANNER + gm.displayScoreboard()).addOption("Reset all").addOption("Exit.").preventArguments();
        int index = stats_menu.run();
        if (index == 1)
        {
            Menu confirmation_menu = Menu(GAME_ASCII_BANNER + gm.displayScoreboard() + "\nAre you sure?").addOption("yes").addOption("no").preventArguments();
            int yn = confirmation_menu.run();
            if (yn == 1) 
            {
                for (auto &&p : gm.getPlayers())
                {
                    p->reset();
                }
            }
        }

        return false;
    };
    return lambda_cb;
}

void SettingsMenu_reloadAllOptions(Menu * m, GameManager& gm)
{
    std::vector<std::string> & options = m->getOptions();
    options[0] = "Menu: Selection Color      " + gm.getBoardTheme().menu_selection_color + COLOR_DEMONSTRATION_CHAR ANSI_RESET;
    options[1] = "Menu: Robot Selected Color " + gm.getBoardTheme().menu_robot_selected_color + COLOR_DEMONSTRATION_CHAR ANSI_RESET;
    options[2] = "Board Color: Background    " + gm.getBoardTheme().background_color + BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET;
    options[3] = "Board Color: Grid          " + gm.getBoardTheme().grid_color + COLOR_DEMONSTRATION_CHAR ANSI_RESET;
    options[4] = "Board Color: Walls         " + gm.getBoardTheme().wall_color + COLOR_DEMONSTRATION_CHAR ANSI_RESET;
    options[5] = "Theme: Color (" + ColorTheme_toString(gm.getBoardTheme().color_theme) + ")";
    options[6] = "Theme: Walls (" + WallsStyle_toString(gm.getBoardTheme().walls_style) + ")";
    options[7] = "Robot randomly replaced each round (" + std::string(gm.robotsAreReplacedEachRound() ? "true" : "false") + ")";
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
                                 .addOption("Menu: Selection Color      ", SettingsMenu::menuSelectionColor_CBBuilder(gm))
                                 .addOption("Menu: Robot Selected Color ", SettingsMenu::menuRobotSelectedColor_CBBuilder(gm))
                                 .addOption("Board Color: Background    ", SettingsMenu::backgroundColor_CBBuilder(gm))
                                 .addOption("Board Color: Grid          ", SettingsMenu::gridColor_CBBuilder(gm))
                                 .addOption("Board Color: Walls         ", SettingsMenu::wallsColor_CBBuilder(gm))
                                 .addOption("Theme: Color ()            ", SettingsMenu::colorTheme_CBBuilder(gm))
                                 .addOption("Theme: Walls ()            ", SettingsMenu::wallsStyle_CBBuilder(gm))
                                 .addOption("Robot randomly replaced each round ", SettingsMenu::robotReplacedEachRound_CBBuilder(gm))
                                 //  .addOption(ANSI_ITALIC "Default." ANSI_RESET_ITALIC) // Not implemented yet
                                 .addOption(ANSI_ITALIC "Exit." ANSI_RESET_ITALIC, [&](int, Menu *)
                                            {running=false; return false; });
        SettingsMenu_reloadAllOptions(&settings_menu, gm);
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
                         .addOption(" Black          " ANSI_BLACK COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BLACK; return false; })
                         .addOption(" Red            " ANSI_RED COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_RED; return false; })
                         .addOption(" Green          " ANSI_GREEN COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_GREEN; return false; })
                         .addOption(" Yellow         " ANSI_YELLOW COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_YELLOW; return false; })
                         .addOption(" Blue           " ANSI_BLUE COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BLUE; return false; })
                         .addOption(" Magenta        " ANSI_MAGENTA COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_MAGENTA; return false; })
                         .addOption(" Cyan           " ANSI_CYAN COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_CYAN; return false; })
                         .addOption(" White          " ANSI_WHITE COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_WHITE; return false; })
                         .addOption(" Light Gray     " ANSI_LIGHT_GRAY COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_LIGHT_GRAY; return false; })
                         .addOption(" Light Gray     " ANSI_LIGHT_GRAY COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_LIGHT_GRAY; return false; })
                         .addOption("Bright Black   " ANSI_BRIGHT_BLACK COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_BLACK; return false; })
                         .addOption("Bright Red     " ANSI_BRIGHT_RED COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_RED; return false; })
                         .addOption("Bright Green   " ANSI_BRIGHT_GREEN COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_GREEN; return false; })
                         .addOption("Bright Yellow  " ANSI_BRIGHT_YELLOW COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_YELLOW; return false; })
                         .addOption("Bright Blue    " ANSI_BRIGHT_BLUE COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_BLUE; return false; })
                         .addOption("Bright Magenta " ANSI_BRIGHT_MAGENTA COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_MAGENTA; return false; })
                         .addOption("Bright Cyan    " ANSI_BRIGHT_CYAN COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_CYAN; return false; })
                         .addOption("Bright White   " ANSI_BRIGHT_WHITE COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BRIGHT_WHITE; return false; });
    colorMenu.run();
    return color;
}
std::string MenuUtils::getBGColorWithMenu(std::string title, std::string selectionColor)
{
    std::string color = "";
    Menu colorMenu = Menu(title)
                         .setColorSelection(selectionColor)
                         .addOption(" Black          " ANSI_BG_BLACK BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BLACK; return false; })
                         .addOption(" Red            " ANSI_BG_RED BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_RED; return false; })
                         .addOption(" Green          " ANSI_BG_GREEN BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_GREEN; return false; })
                         .addOption(" Yellow         " ANSI_BG_YELLOW BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_YELLOW; return false; })
                         .addOption(" Blue           " ANSI_BG_BLUE BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BLUE; return false; })
                         .addOption(" Magenta        " ANSI_BG_MAGENTA BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_MAGENTA; return false; })
                         .addOption(" Cyan           " ANSI_BG_CYAN BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_CYAN; return false; })
                         .addOption(" White          " ANSI_BG_WHITE BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_WHITE; return false; })
                         .addOption(" Bright Black   " ANSI_BG_BRIGHT_BLACK BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_BLACK; return false; })
                         .addOption("Bright Red     " ANSI_BG_BRIGHT_RED BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_RED; return false; })
                         .addOption("Bright Green   " ANSI_BG_BRIGHT_GREEN BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_GREEN; return false; })
                         .addOption("Bright Yellow  " ANSI_BG_BRIGHT_YELLOW BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_YELLOW; return false; })
                         .addOption("Bright Blue    " ANSI_BG_BRIGHT_BLUE BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_BLUE; return false; })
                         .addOption("Bright Magenta " ANSI_BG_BRIGHT_MAGENTA BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_MAGENTA; return false; })
                         .addOption("Bright Cyan    " ANSI_BG_BRIGHT_CYAN BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_CYAN; return false; })
                         .addOption("Bright White   " ANSI_BG_BRIGHT_WHITE BG_COLOR_DEMONSTRATION_CHAR ANSI_RESET, [&](int, Menu *)
                                    {color = ANSI_BG_BRIGHT_WHITE; return false; });
    colorMenu.run();
    return color;
}


Menu::MenuCallback_t SettingsMenu::menuSelectionColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().menu_selection_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Menu Selection Color", gm.getBoardTheme().menu_selection_color);
        m->setColorSelection(gm.getBoardTheme().menu_selection_color);
        gm.setColorTheme(ColorTheme::CUSTOM);
        SettingsMenu_reloadAllOptions(m, gm);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::menuRobotSelectedColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().menu_robot_selected_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Menu Robot Selected Color", gm.getBoardTheme().menu_selection_color);
        gm.setColorTheme(ColorTheme::CUSTOM);
        SettingsMenu_reloadAllOptions(m, gm);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::backgroundColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().background_color = MenuUtils::getBGColorWithMenu(GAME_ASCII_BANNER "Background Color", gm.getBoardTheme().menu_selection_color);
        gm.setColorTheme(ColorTheme::CUSTOM);
        SettingsMenu_reloadAllOptions(m, gm);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::gridColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().grid_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Grid Color", gm.getBoardTheme().menu_selection_color);
        gm.setColorTheme(ColorTheme::CUSTOM);
        SettingsMenu_reloadAllOptions(m, gm);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::wallsColor_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.getBoardTheme().wall_color = MenuUtils::getColorWithMenu(GAME_ASCII_BANNER "Walls Color", gm.getBoardTheme().menu_selection_color);
        gm.setColorTheme(ColorTheme::CUSTOM);
        SettingsMenu_reloadAllOptions(m, gm);
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::wallsStyle_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu menu = Menu(GAME_ASCII_BANNER "Theme: Walls Style").addOption("SIMPLE_WALLS").addOption("DOUBLE_WALLS").addOption("Exit.");
        int index = menu.run();
        if (index != 3)
        {
            gm.setWallsStyle(WallsStyle(index-1));
            SettingsMenu_reloadAllOptions(m, gm);
        }
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::colorTheme_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {

        Menu menu = Menu(GAME_ASCII_BANNER "Theme: Color").addOption("LIGHT_THEME").addOption("DARK_THEME").addOption("CUSTOM").addOption("Exit.");
        int index = menu.run();
        if (index != 4)
        {
            gm.setColorTheme(ColorTheme(index-1));
            SettingsMenu_reloadAllOptions(m, gm);
        }
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t SettingsMenu::robotReplacedEachRound_CBBuilder(GameManager &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        gm.replaceRobotsEachRound(!gm.robotsAreReplacedEachRound());
        std::string temp = (gm.robotsAreReplacedEachRound() ? "true" : "false");
        m->getOptions()[pos - 1] = "Robot randomly replaced each round (" + temp + ")";
        return false;
    };
    return lambda_cb;
}