#pragma once

#include "Frame.h"

class QuarterBoard
{
private:
    int id;
    Frame frames[8][8];

public:
    /* Constructors */
    QuarterBoard(int id);
    QuarterBoard(Frame f[8][8], int id);

    /* Getters */
    int getID();
    Frame getFrame(int x, int y) const;

    /* Methods */
    QuarterBoard applySymmetry() const;
};
