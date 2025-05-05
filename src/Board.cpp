#include <algorithm>
#include <vector>

#include "Board.h"

std::vector<Tile> TILES = {
    Tile(RED, CIRCLE),
    Tile(RED, SQUARE),
    Tile(RED, TRIANGLE),
    Tile(RED, STAR),
    Tile(GREEN, CIRCLE),
    Tile(GREEN, SQUARE),
    Tile(GREEN, TRIANGLE),
    Tile(GREEN, STAR),
    Tile(BLUE, CIRCLE),
    Tile(BLUE, SQUARE),
    Tile(BLUE, TRIANGLE),
    Tile(BLUE, STAR),
    Tile(YELLOW, CIRCLE),
    Tile(YELLOW, SQUARE),
    Tile(YELLOW, TRIANGLE),
    Tile(YELLOW, STAR)};

/* Constructors */

Board::Board()
: quarterBoards{{QuarterBoard(0), QuarterBoard(1)}, {QuarterBoard(2), QuarterBoard(3)}}
{
   
    this->quarterBoards[0][0] = this->generateQuarterBoard(true, true);
    this->quarterBoards[0][1] = this->generateQuarterBoard(true, false);
    this->quarterBoards[1][0] = this->generateQuarterBoard(false, true);
    this->quarterBoards[1][1] = this->generateQuarterBoard(false, false);
}

/* Getters */

Frame Board::getFrame(int x, int y)
{
    /* Top left frame coordinates = (0,0) */
    int quarter_x = (x < 8) ? 0 : 1;
    int quarter_y = (y < 8) ? 1 : 0;
    return this->quarterBoards[quarter_x][quarter_y].getFrame(x % 8, y % 8);
}

/* Methods */

QuarterBoard Board::generateQuarterBoard(bool top, bool left)
{
    Frame frames[8][8];
    // Génerer les bordures 
    for (int i = 0; i<8 ; i++)
    {
        for(int j = 0; j<8 ; j++)
        { 
            // Contours
            frames[i][j].setWall(top && j==0, UP);
            frames[i][j].setWall(!top && j==7, DOWN);
            frames[i][j].setWall(!left && i==7, RIGHT);
            frames[i][j].setWall(left && i==0, LEFT);
            
            // Centre
            frames[i][j].setWall(top && left && i==7 && j==7, UP);
            frames[i][j].setWall(top && left && i==6 && j==7, DOWN);
            frames[i][j].setWall(top && left && i==7 && j==7, LEFT);
            frames[i][j].setWall(top && left && i==7 && j==6, RIGHT);


            frames[i][j].setWall(!top && left && i==0 && j==7, LEFT);
            frames[i][j].setWall(!top && left && i==0 && j==6, RIGHT);
            frames[i][j].setWall(!top && left && i==0 && j==7, DOWN);
            frames[i][j].setWall(!top && left && i==1 && j==7, UP);

            frames[i][j].setWall(!top && !left && i==0 && j==0, DOWN);
            frames[i][j].setWall(!top && !left && i==0 && j==1, UP);
            frames[i][j].setWall(!top && !left && i==0 && j==0, RIGHT);
            frames[i][j].setWall(!top && !left && i==1 && j==0, LEFT);


            frames[i][j].setWall(top && !left && i==7 && j==0, UP);
            frames[i][j].setWall(top && !left && i==6 && j==0, DOWN);
            frames[i][j].setWall(top && !left && i==7 && j==0, RIGHT);
            frames[i][j].setWall(top && !left && i==7 && j==1, LEFT);



        } 
    }

    // Générer les murs intérieurs 


   
}

void Board::generate()
{
    // /* Random shuffle the quarterboards */
    // std::vector<QuarterBoard> quarterboards = {this->quarterBoards[0][0],
    //                                            this->quarterBoards[0][1],
    //                                            this->quarterBoards[1][0],
    //                                            this->quarterBoards[1][1]};
    // std::random_shuffle(quarterboards.begin(), quarterboards.end());
    // this->quarterBoards[0][0] = quarterboards[0];
    // this->quarterBoards[0][1] = quarterboards[1];
    // this->quarterBoards[1][0] = quarterboards[2];
    // this->quarterBoards[1][1] = quarterboards[3];

    // /* Randomly apply symetry to the quarterboards */
    // for (int x = 0; x < 2; x++)
    // {
    //     for (int y = 0; y < 2; y++)
    //     {
    //         if (rand() % 2 == 0)
    //         {
    //             this->quarterBoards[x][y] = this->quarterBoards[x][y].ApplySymmetry();
    //         }
    //     }
    // }
    this->quarterBoards[0][0] = this->generateQuarterBoard(true, true);
    this->quarterBoards[0][1] = this->generateQuarterBoard(true, false);
    this->quarterBoards[1][0] = this->generateQuarterBoard(false, true);
    this->quarterBoards[1][1] = this->generateQuarterBoard(false, false);
}
