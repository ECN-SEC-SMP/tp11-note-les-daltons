#pragma once

#include <vector>
#include "QuarterBoard.h"

class Board
{
private:
    QuarterBoard quarterBoards[2][2];

public:
    Board();
    void generate();
    Frame getFrame(int x, int y);
};

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
    Tile(YELLOW, STAR),
    Tile(RAINBOW, STAR)
};