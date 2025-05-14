#include <gtest/gtest.h>

#include "Player.h"

#define PLAYER_NAME "louis"

Player player(PLAYER_NAME);

/* Name --------------------------------------------------------------------- */

TEST(Player_name, InitName)
{
    EXPECT_EQ(player.getName(), PLAYER_NAME);
}

/* Score -------------------------------------------------------------------- */

TEST(Player_score, InitScore)
{
    EXPECT_EQ(player.getScore(), 0);
}

TEST(Player_score, IncrementHandlesPositiveInput)
{
    player.incrementScore(3);
    EXPECT_EQ(player.getScore(), 3);
}

TEST(Player_score, IncrementHandlesNegativeInput)
{
    player.incrementScore(-10);
    EXPECT_EQ(player.getScore(), 0);
}

/* Prediction --------------------------------------------------------------- */

TEST(Player_prediction, InitPrediction)
{
    EXPECT_EQ(player.getPrediction(), 0);
}

TEST(Player_prediction, SetterHandlesPositiveInput)
{
    player.setPrediction(3);
    EXPECT_EQ(player.getPrediction(), 3);
}

TEST(Player_prediction, SetterHandlesNegativeInput)
{
    player.setPrediction(-10);
    EXPECT_EQ(player.getPrediction(), 0);
}

/* NbMoves ------------------------------------------------------------------ */

TEST(Player_nbMoves, InitNbMoves)
{
    EXPECT_EQ(player.getNbMoves(), 0);
}

TEST(Player_nbMoves, Increment)
{
    player.incrementMoves();
    EXPECT_EQ(player.getNbMoves(), 1);
}

/* NbRoundsPlayed ----------------------------------------------------------- */

TEST(Player_nbRoundsPlayed, InitNbRoundsPlayed)
{
    EXPECT_EQ(player.getRoundsPlayed(), 0);
}
TEST(Player_nbRoundsPlayed, Increment)
{
    player.incrementRoundsPlayed();
    EXPECT_EQ(player.getRoundsPlayed(), 1);
}