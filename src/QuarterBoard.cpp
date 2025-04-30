#include "QuarterBoard.h"

QuarterBoard::QuarterBoard(int id)
 : id(id)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->frames[i][j] = Frame();
        }
    }
}

QuarterBoard::QuarterBoard(Frame f[8][8], int id)
 : id(id)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->frames[i][j] = f[i][j];
        }
    }
}

int QuarterBoard::getID() {
    return this->id;
}

Frame QuarterBoard::getFrame(int x, int y) const {
    return this->frames[x][y];
}

void QuarterBoard::getFrames(Frame f[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            f[i][j] = this->frames[i][j];
        }
    }
}

QuarterBoard QuarterBoard::ApplySymmetry() const {
    Frame tmp[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int j2 = 7 - j;
            Frame frame_tmp = this->frames[i][j2];
            bool walls[4] = {false, false, false, false};
            walls[0] = frame_tmp.getWalls()[0];
            walls[1] = frame_tmp.getWalls()[1];
            walls[2] = frame_tmp.getWalls()[3];
            walls[3] = frame_tmp.getWalls()[2];
            tmp[i][j] = Frame(frame_tmp.getTile(), walls);
        }
    }
    return QuarterBoard(tmp, this->id + 100);
}
