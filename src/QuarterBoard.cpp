#include "QuarterBoard.h"

/* Constructors */
QuarterBoard::QuarterBoard()
{
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         this->frames[i][j] = Frame();
    //     }
    // }
}

QuarterBoard::QuarterBoard(Frame f[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->frames[i][j] = f[i][j];
        }
    }
}

/* Getters */

Frame QuarterBoard::getFrame(int x, int y) const
{
    return this->frames[x][y];
}

/* Methods */
QuarterBoard QuarterBoard::applySymmetry() const
{
    Frame tmp[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int j2 = 7 - j;
            Frame frame_tmp = this->frames[i][j2];
            bool walls[4] = {false, false, false, false};
            walls[UP] = frame_tmp.getWalls()[UP];
            walls[DOWN] = frame_tmp.getWalls()[DOWN];
            walls[LEFT] = frame_tmp.getWalls()[RIGHT];
            walls[RIGHT] = frame_tmp.getWalls()[LEFT];
            tmp[i][j] = Frame(frame_tmp.getTile(), walls);
        }
    }
    return QuarterBoard(tmp);
}
