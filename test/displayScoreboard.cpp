#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include "TestGameManager.h"
#include "TestPlayer.h"
#include "TestUtils.h"
#include "Utils.h"

// #define GENERATE_EXPECTED

TEST(displayScoreboard, NoPlayers)
{
    const char *filename = "scoreboard_noPlayers.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif

    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());    
}

/* Success rate ------------------------------------------------------------- */

TEST(displayScoreboard, PositiveSuccessRate)
{
    const char *filename = "scoreboard_PositiveSuccessRate.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);
    
    /* 3 rounds, 2 wins: 66% success rate */
    tplayer->setNbRoundsPlayed(3);
    tplayer->setScore(2);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, ZeroSuccessRate)
{
    const char *filename = "scoreboard_ZeroSuccessRate.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);
    
    /* 10 rounds, 0 wins: 0% success rate */
    tplayer->setNbRoundsPlayed(10);
    tplayer->setScore(0);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, OverflowSuccessRate)
{
    const char *filename = "scoreboard_OverflowSuccessRate.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);
    
    /* 2 rounds, 6 wins: 300% success rate */
    tplayer->setNbRoundsPlayed(2);
    tplayer->setScore(6);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, DivisionByZeroSuccessRate)
{
    const char *filename = "scoreboard_DivisionByZeroSuccessRate.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);

    /* 0 rounds, 6 wins: ?% success rate */
    tplayer->setNbRoundsPlayed(0);
    tplayer->setScore(6);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif

    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, MultiplePlayersNoWinner)
{
    const char *filename = "scoreboard_MultiplePlayersNoWinner.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayers */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer_dada = (TestPlayer *)gm.getPlayer(0);
    tplayer_dada->setNbRoundsPlayed(2);
    tplayer_dada->setScore(0);

    gm.addPlayer(new TestPlayer("Louiiiiiiiiis"));
    TestPlayer * tplayer_louis = (TestPlayer *)gm.getPlayer(1);
    tplayer_louis->setNbRoundsPlayed(3);
    tplayer_louis->setScore(0);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

/* Differents amounts of players -------------------------------------------- */

TEST(displayScoreboard, OnePlayer)
{
    const char *filename = "scoreboard_onePlayer.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayer */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer = (TestPlayer *)gm.getPlayer(0);

    tplayer->setNbRoundsPlayed(2);
    tplayer->setScore(2);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, TwoPlayers)
{
    const char *filename = "scoreboard_twoPlayers.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayers */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer_dada = (TestPlayer *)gm.getPlayer(0);
    tplayer_dada->setNbRoundsPlayed(2);
    tplayer_dada->setScore(2);

    gm.addPlayer(new TestPlayer("Louiiiiiiiiis"));
    TestPlayer * tplayer_louis = (TestPlayer *)gm.getPlayer(1);
    tplayer_louis->setNbRoundsPlayed(3);
    tplayer_louis->setScore(5);

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}

TEST(displayScoreboard, MoreThanThreePlayers)
{
    const char *filename = "scoreboard_moreThanThreePlayers.txt";

    /* Create TestGameManager */
    TestGameManager gm = initTestGameManager();

    /* Create TestPlayers */
    gm.addPlayer(new TestPlayer("Dada"));
    TestPlayer * tplayer_dada = (TestPlayer *)gm.getPlayer(0);
    tplayer_dada->setNbRoundsPlayed(5);
    tplayer_dada->setScore(3);

    gm.addPlayer(new TestPlayer("Louiiiiiiiis"));
    TestPlayer * tplayer_louis = (TestPlayer *)gm.getPlayer(1);
    tplayer_louis->setNbRoundsPlayed(4);
    tplayer_louis->setScore(2);

    gm.addPlayer(new TestPlayer("Po"));

    gm.addPlayer(new TestPlayer("ouais ouais ouais"));

    /* Generate expected scoreboard */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayScoreboard());
#endif
    
    /* Test */
    const std::string scoreboard = gm.displayScoreboard();
    const std::string expected_scoreboard = readFile(filename);
    EXPECT_STREQ(scoreboard.c_str(), expected_scoreboard.c_str());
}