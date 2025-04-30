#pragma once

#include "QuarterBoard.h"

class Board
{
    private:
        QuarterBoard quarterBoards[2][2];
    public:
        Board();
        void generate();
        Frame getFrame(int x, int y);
        QuarterBoard getQuarterBoard(int x, int y);
};
