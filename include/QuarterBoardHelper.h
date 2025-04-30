#include "QuarterBoard.h"
#include <iostream>

bool tmp[4] = {false, false, false, true};

Frame testf = Frame(new Tile(Color::BLUE, Shape::CIRCLE), (bool[4]){false, false, false, true});

Frame framesQuarter1[8][8] = {
    {Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::GREEN, Shape::TRIANGLE), (bool[4]){true, false, true, false}), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, true, false, true}), Frame(nullptr, (bool[4]){false, false, true, false})},
    {Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::RED, Shape::CIRCLE), (bool[4]){false, true, true, false}), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame()},
    {Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame()},
    {Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame(new Tile(Color::BLUE, Shape::SQUARE), (bool[4]){true, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(), Frame()},
    {Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()}};

const QuarterBoard Quarter1 = QuarterBoard(framesQuarter1, true);

Frame framesQuarter2[8][8] = {
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::YELLOW, Shape::SQUARE), (bool[4]){false, true, true, false}), Frame(), Frame()},
    {Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::GREEN, Shape::CIRCLE), (bool[4]){false, true, true, false}), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(nullptr, (bool[4]){false, true, false, false}), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(new Tile(Color::BLUE, Shape::STAR), (bool[4]){true, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false})},
    {Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true})},
    {Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(), Frame(new Tile(Color::RED, Shape::TRIANGLE), (bool[4]){false, true, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame()}};

const QuarterBoard Quarter2 = QuarterBoard(framesQuarter2, 2);

Frame framesQuarter3[8][8] = {
    {Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(new Tile(Color::RED, Shape::SQUARE), (bool[4]){false, true, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(new Tile(Color::YELLOW, Shape::CIRCLE), (bool[4]){true, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame()},
    {Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::GREEN, Shape::STAR), (bool[4]){false, true, true, false}), Frame(), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::BLUE, Shape::TRIANGLE), (bool[4]){true, false, true, false}), Frame(), Frame(), Frame(nullptr, (bool[4]){false, true, false, false})},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, true, false, false})},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()}};

const QuarterBoard Quarter3 = QuarterBoard(framesQuarter3, 3);

Frame framesQuarter4[8][8] = {
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::YELLOW, Shape::TRIANGLE), (bool[4]){false, true, true, false}), Frame()},
    {Frame(), Frame(new Tile(Color::GREEN, Shape::SQUARE), (bool[4]){false, true, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame()},
    {Frame(), Frame(nullptr, (bool[4]){true, false, false, false}), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(new Tile(Color::RED, Shape::STAR), (bool[4]){true, false, true, false}), Frame(), Frame(), Frame(nullptr, (bool[4]){false, true, false, false})},
    {Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){true, false, false, false})},
    {Frame(new Tile(Color::RAINBOW, Shape::STAR), (bool[4]){true, false, true, false}), Frame(), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(new Tile(Color::BLUE, Shape::CIRCLE), (bool[4]){true, false, false, true}), Frame(nullptr, (bool[4]){false, true, false, false}), Frame(), Frame(), Frame(), Frame()},
    {Frame(), Frame(), Frame(), Frame(), Frame(nullptr, (bool[4]){false, false, false, true}), Frame(nullptr, (bool[4]){false, false, true, false}), Frame(), Frame()}};

const QuarterBoard Quarter4 = QuarterBoard(framesQuarter4, 4);

void printQuarter(const QuarterBoard &quarter)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Frame frame = quarter.getFrame(i, j);
            if (frame.getTile() != nullptr)
            {
                std::cout << "T ";
            }
            else
            {
                std::cout << ". ";
            }
            if (frame.getWalls()[0])
            {
                std::cout << "U ";
            }
            else
            {
                std::cout << ". ";
            }
            if (frame.getWalls()[1])
            {
                std::cout << "D ";
            }
            else
            {
                std::cout << ". ";
            }
            if (frame.getWalls()[2])
            {
                std::cout << "L ";
            }
            else
            {
                std::cout << ". ";
            }
            if (frame.getWalls()[3])
            {
                std::cout << "R ";
            }
            else
            {
                std::cout << ". ";
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}