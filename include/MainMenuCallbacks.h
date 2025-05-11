#pragma once

#include "Menu.h"
#include "GameManager.h"

/* some stuff */
#define CONTINUE_ON_ENTER_PROMPT                              \
    std::cin.clear();                                         \
    std::cout << "Press [ENTER] to continue..." << std::endl; \
    getchar();
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

namespace MainMenu
{
    bool CB_printHelp(int pos, Menu *m);
    Menu::MenuCallback_t play_CBBuilder(GameManager &gm);
    Menu::MenuCallback_t addPlayer_CBBuilder(GameManager &gm);
    Menu::MenuCallback_t removePlayer_CBBuilder(GameManager &gm);
    Menu::MenuCallback_t regenerateBoard_CBBuilder(GameManager &gm);
    bool CB_notImplementedYet(int pos, Menu *m);
} // namespace MainMenu
