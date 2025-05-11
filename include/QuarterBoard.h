#pragma once

#include "Frame.h"

class QuarterBoard
{
private:
    Frame frames[8][8];

public:
    /* Constructors */
    QuarterBoard();
    QuarterBoard(Frame f[8][8]);

    /* Getters */
    Frame getFrame(int x, int y) const;

    /* Methods */
    QuarterBoard applySymmetry() const;
};
