#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include "TestPlayer.h"
#include "TestUtils.h"

// #define GENERATE_EXPECTED

/* Differents amounts of players -------------------------------------------- */

TEST(displayRoundResults, OnePlayer)
{
    const char *filename = "roundResults_onePlayer.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);

    tplayer->setPrediction(5);

    /* Generate expected roundResults */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayRoundResults());
#endif
    
    /* Test */
    const std::string roundResults = gm.displayRoundResults();
    const std::string expected_roundResults = readFile(filename);
    EXPECT_STREQ(roundResults.c_str(), expected_roundResults.c_str());
}

TEST(displayRoundResults, TwoPlayers)
{
    const char *filename = "roundResults_twoPlayers.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayers */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer_dada = (TestPlayer *)gm.getPlayer(0);
    tplayer_dada->setPrediction(2);

    gm.addPlayer(new TestPlayer("Louiiiiiiiiis"));
    TestPlayer * tplayer_louis = (TestPlayer *)gm.getPlayer(1);
    tplayer_louis->setPrediction(3);

    /* Generate expected roundResults */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayRoundResults());
#endif
    
    /* Test */
    const std::string roundResults = gm.displayRoundResults();
    const std::string expected_roundResults = readFile(filename);
    EXPECT_STREQ(roundResults.c_str(), expected_roundResults.c_str());
}



TEST(displayRoundResults, TwoPlayersWithWinner)
{
    const char *filename = "roundResults_twoPlayersWithWinner.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayers */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer_dada = (TestPlayer *)gm.getPlayer(0);
    tplayer_dada->setPrediction(3);
    tplayer_dada->setNbMoves(2);

    gm.addPlayer(new TestPlayer("Louiiiiiiiiis"));
    TestPlayer * tplayer_louis = (TestPlayer *)gm.getPlayer(1);
    tplayer_louis->setPrediction(4);

    gm.setWinner(tplayer_dada);

    /* Generate expected roundResults */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayRoundResults());
#endif
    
    /* Test */
    const std::string roundResults = gm.displayRoundResults();
    const std::string expected_roundResults = readFile(filename);
    EXPECT_STREQ(roundResults.c_str(), expected_roundResults.c_str());
}