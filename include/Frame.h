#pragma once

#include <array>
#include "typedef.h"
#include "Tile.h"

class Frame
{
private:
    Tile *tile;
    std::array<bool,4> wall; 
public:
    Frame();
    Frame(Tile *t, std::array<bool,4> w);
    Tile getTile();
    std::array<bool,4> getWall();
    bool canMove(Direction d);
};