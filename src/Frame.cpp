#include "Frame.h"

Frame::Frame()
    : tile(nullptr), walls{false, false, false, false} {}

Frame::Frame(Tile *t, bool walls[4])
    : tile(t)
{
    for (size_t i = 0; i < 4; ++i)
    {
        this->walls[i] = walls[i];
    }
}

Tile *Frame::getTile()
{
    return this->tile;
}

bool *Frame::getWalls()
{
    return this->walls;
}

bool Frame::canMove(Direction d)
{
    return this->walls[d];
}