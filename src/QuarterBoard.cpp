#include "QuarterBoard.h"

QuarterBoard::QuarterBoard()
 : id(0)
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

Frame QuarterBoard::getFrame(int x, int y) {
    return this->frames[x][y];
}

void QuarterBoard::getFrames(Frame f[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            f[i][j] = this->frames[i][j];
        }
    }
}
