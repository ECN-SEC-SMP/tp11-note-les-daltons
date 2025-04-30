#include "QuarterBoard.h"

QuarterBoard::QuarterBoard(int id)
    : id(id)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->frames[i][j] = Frame();
        }
    }
}

QuarterBoard::QuarterBoard(Frame f[8][8], int id)
    : id(id)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->frames[i][j] = f[i][j];
        }
    }
}

int QuarterBoard::getID()
{
    return this->id;
}

Frame QuarterBoard::getFrame(int x, int y) const
{
    return this->frames[x][y];
}

void QuarterBoard::getFrames(Frame f[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            f[i][j] = this->frames[i][j];
        }
    }
}

QuarterBoard QuarterBoard::ApplySymmetry() const
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
    return QuarterBoard(tmp, this->id + 100);
}
