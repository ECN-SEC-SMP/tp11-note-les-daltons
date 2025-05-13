#pragma once

#include "GameManager.h"
#include "TestPlayer.h"

class TestGameManager : public GameManager
{
public:
    TestGameManager() : GameManager() {}
    void setWinner(Player *player) { this->winner = player;}
};