#include "Board.h"

Board::Board() : quarterBoards{{QuarterBoard(0), QuarterBoard(1)},
                              {QuarterBoard(2), QuarterBoard(3)}}
{}

void Board::generate() {}