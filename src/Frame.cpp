#include "Frame.h"

Frame::Frame(Tile *t, std::array<bool,4> w)
 : tile(t), wall(w) {}


Tile Frame::getTile() {
    return *this->tile;
}

std::array<bool,4> Frame::getWall() {
    return this->wall;
}

bool Frame::canMove(Direction d){
    if (d == UP) {
        return !this->wall[0];
    } else if (d == DOWN) {
        return !this->wall[1];
    } else if (d == LEFT) {
        return !this->wall[2];
    } else if (d == RIGHT) {
        return !this->wall[3];
    }
    return false;
}