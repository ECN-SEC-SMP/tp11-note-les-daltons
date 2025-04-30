#pragma once

#include <array>
#include <cstddef>
#include "typedef.h"
#include "Tile.h"

class Frame
{
private:
    /// @brief tile is a pointer to the tile object
    Tile *tile;
    /// @brief wall[0]: up, wall[1]: down, wall[2]: left, wall[3]: right
    bool walls[4];

public:
    Frame();
    Frame(Tile *t, bool wall[4]);
    Frame(Tile *t, const bool wall[4]);
    Tile *getTile();
    bool *getWalls();
    bool canMove(Direction d);
};