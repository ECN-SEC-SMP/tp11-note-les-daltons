#pragma once

#include "GameManager.h"

class TestGameManager : public GameManager
{
public:
    TestGameManager() : GameManager() {}
    void setWinner(Player *player) { this->winner = player;}
};