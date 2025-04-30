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
    /// @brief walls[0]: up, walls[1]: down, walls[2]: left, walls[3]: right
    bool walls[4];

public:
    Frame();
    Frame(Tile *t, bool walls[4]);
    Frame(Tile *t, const bool walls[4]);
    Tile *getTile();
    bool *getWalls();
    bool canMove(Direction d);
};