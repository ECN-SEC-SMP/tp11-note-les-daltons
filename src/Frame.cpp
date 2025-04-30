#include "Frame.h"

Frame::Frame()
 : tile(nullptr), walls{false, false, false, false} {}

Frame::Frame(Tile *t, bool wall[4])
 : tile(t) {
    for (size_t i = 0; i < 4; ++i) {
        this->walls[i] = wall[i];
    }
}


Tile * Frame::getTile() {
    return this->tile;
}

bool* Frame::getWalls() {
    return this->walls;
}

bool Frame::canMove(Direction d){
    if (d == UP) {
        return !this->walls[0];
    } else if (d == DOWN) {
        return !this->walls[1];
    } else if (d == LEFT) {
        return !this->walls[2];
    } else if (d == RIGHT) {
        return !this->walls[3];
    }
    return false;
}