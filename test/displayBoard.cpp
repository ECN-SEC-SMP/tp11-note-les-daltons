#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include "Board.h"
#include "QuarterBoardHelper.h"
#include "TestUtils.h"

// #define GENERATE_EXPECTED

TEST(displayBoard, board_predefined)
{
    const char *filename = "board.txt";

    /* Create TestGameManager */
    TestGameManager gm;

    /* Setup Board */
    QuarterBoard qb_array[2][2] = {{Quarter1, Quarter2},{Quarter3, Quarter4}};
    Board board(qb_array);
    gm.setBoard(board);

    /* Generate expected results */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayBoard());
#endif
    
    /* Test */
    const std::string results = gm.displayBoard();
    const std::string expected_results = readFile(filename);
    EXPECT_STREQ(results.c_str(), expected_results.c_str());
}

TEST(displayBoard, board_empty)
{
    const char *filename = "board_empty.txt";

    /* Create TestGameManager */
    TestGameManager gm;

    /* Generate expected results */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayEmptyBoard());
#endif
    
    /* Test */
    const std::string results = gm.displayEmptyBoard();
    const std::string expected_results = readFile(filename);
    EXPECT_STREQ(results.c_str(), expected_results.c_str());
}

