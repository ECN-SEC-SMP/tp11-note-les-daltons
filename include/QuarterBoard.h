#pragma once

#include "Frame.h"

class QuarterBoard
{
    private:
        int id;
        Frame frames[8][8];
    public:
        QuarterBoard();
        QuarterBoard(Frame f[8][8], int id);
        int getID();
        Frame getFrame(int x, int y);
        void getFrames(Frame f[8][8]);
};
