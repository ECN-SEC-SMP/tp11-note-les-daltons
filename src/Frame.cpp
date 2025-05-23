#include "Frame.h"

/* Constructors */
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

/* Getters */
Tile *Frame::getTile()
{
    return this->tile;
}

bool *Frame::getWalls()
{
    return this->walls;
}

/* Setters */
void Frame::setTile(Tile *t)
{
    this->tile = t;
}

void Frame::setWalls(const bool walls[4])
{
    for (size_t i = 0; i < 4; ++i)
    {
        this->walls[i] = walls[i];
    }
}

void Frame::setWall(bool wall, Direction d)
{
    this->walls[d] = wall;
}

/* Methods */
bool Frame::canMove(Direction d)
{
    return !this->walls[d];
}