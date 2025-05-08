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
    /* Contructors */
    Frame();
    Frame(Tile *t, bool walls[4]);
    Frame(Tile *t, const bool walls[4]);

    /* Getters */
    Tile *getTile();
    bool *getWalls();

    /* Setters */
    void setTile(Tile *t);
    void setWalls(const bool walls[4]);
    void setWall(bool wall, Direction d);

    /* Methods */
    bool canMove(Direction d);
};