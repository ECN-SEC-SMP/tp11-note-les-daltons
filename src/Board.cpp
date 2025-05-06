#include <algorithm>
#include <vector>
#include <ctime>

#include "Board.h"
#include "QuarterBoardHelper.h"

/* Constructors */

Board::Board() : quarterBoards{{QuarterBoard(0), QuarterBoard(1)},
                               {QuarterBoard(2), QuarterBoard(3)}}
{
}

/* Getters */

Frame Board::getFrame(int x, int y)
{
    /* Top left frame coordinates = (0,0) */
    int quarter_x = (x < 8) ? 0 : 1;
    int quarter_y = (y < 8) ? 0 : 1;
    return this->quarterBoards[quarter_x][quarter_y].getFrame(x % 8, y % 8);
}

/* Methods */

void Board::generate()
{
    /* Generate the quarterboards */
    this->quarterBoards[0][0] = Quarter1;
    this->quarterBoards[0][1] = Quarter2;
    this->quarterBoards[1][0] = Quarter3;
    this->quarterBoards[1][1] = Quarter4;

    /* Random shuffle the quarterboards */
    // std::vector<QuarterBoard> quarterboards = {this->quarterBoards[0][0],
    //                                            this->quarterBoards[0][1],
    //                                            this->quarterBoards[1][0],
    //                                            this->quarterBoards[1][1]};
    // // std::srand ( unsigned ( std::time(0) ) );
    // std::random_shuffle(quarterboards.begin(), quarterboards.end());
    // this->quarterBoards[0][0] = quarterboards[0];
    // this->quarterBoards[0][1] = quarterboards[1];
    // this->quarterBoards[1][0] = quarterboards[2];
    // this->quarterBoards[1][1] = quarterboards[3];

    /* Randomly apply symetry to the quarterboards */
    // for (int x = 0; x < 2; x++)
    // {
    //     for (int y = 0; y < 2; y++)
    //     {
    //         if (rand() % 2 == 0)
    //         {
    //             this->quarterBoards[x][y] = this->quarterBoards[x][y].applySymmetry();
    //         }
    //     }
    // }
}
