#pragma once

#include "Player.h"

class TestPlayer : public Player
{
public:
    TestPlayer(std::string name) : Player(name) {}
    void setNbMoves(int n) { this->nbMoves = n; }
    void setNbRoundsPlayed(int n) { this->nbRoundsPlayed = n; }
    void setScore(int s) { this->score = s; } 
};