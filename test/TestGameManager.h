#pragma once

#include "GameManager.h"

class TestGameManager : public GameManager
{
public:
    void setWinner(Player *player) { this->winner = player;};
};