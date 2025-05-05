#include "Board.h"

Board::Board() : quarterBoards{{QuarterBoard(0), QuarterBoard(1)},
                               {QuarterBoard(2), QuarterBoard(3)}}
{
}

void Board::generate() {}

Frame Board::getFrame(int x, int y)
{
    int quarter_x = x / 8;
    int quarter_y = y / 8;
    int frame_x = x % 8;
    int frame_y = y % 8;

    return quarterBoards[quarter_x][quarter_y].getFrame(frame_x, frame_y);
}