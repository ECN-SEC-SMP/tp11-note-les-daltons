#include <gtest/gtest.h>

#include "Frame.h"

TEST(Frame_setWall, UP)
{
    Frame frame = Frame();
    frame.setWall(true, UP);
    EXPECT_TRUE(frame.getWalls()[UP]);
    frame.setWall(false, UP);
    EXPECT_FALSE(frame.getWalls()[UP]);
}

TEST(Frame_setWall, DOWN)
{
    Frame frame = Frame();
    frame.setWall(true, DOWN);
    EXPECT_TRUE(frame.getWalls()[DOWN]);
    frame.setWall(false, DOWN);
    EXPECT_FALSE(frame.getWalls()[DOWN]);
}

TEST(Frame_setWall, LEFT)
{
    Frame frame = Frame();
    frame.setWall(true, LEFT);
    EXPECT_TRUE(frame.getWalls()[LEFT]);
    frame.setWall(false, LEFT);
    EXPECT_FALSE(frame.getWalls()[LEFT]);
}

TEST(Frame_setWall, RIGHT)
{
    Frame frame = Frame();
    frame.setWall(true, RIGHT);
    EXPECT_TRUE(frame.getWalls()[RIGHT]);
    frame.setWall(false, RIGHT);
    EXPECT_FALSE(frame.getWalls()[RIGHT]);
}

TEST(Frame_canMove, UP)
{
    Frame frame = Frame();
    frame.setWall(true, UP);
    EXPECT_FALSE(frame.canMove(UP));
    frame.setWall(false, UP);
    EXPECT_TRUE(frame.canMove(UP));
}

TEST(Frame_canMove, DOWN)
{
    Frame frame = Frame();
    frame.setWall(true, DOWN);
    EXPECT_FALSE(frame.canMove(DOWN));
    frame.setWall(false, DOWN);
    EXPECT_TRUE(frame.canMove(DOWN));
}

TEST(Frame_canMove, LEFT)
{
    Frame frame = Frame();
    frame.setWall(true, LEFT);
    EXPECT_FALSE(frame.canMove(LEFT));
    frame.setWall(false, LEFT);
    EXPECT_TRUE(frame.canMove(LEFT));
}

TEST(Frame_canMove, RIGHT)
{
    Frame frame = Frame();
    frame.setWall(true, RIGHT);
    EXPECT_FALSE(frame.canMove(RIGHT));
    frame.setWall(false, RIGHT);
    EXPECT_TRUE(frame.canMove(RIGHT));
}
