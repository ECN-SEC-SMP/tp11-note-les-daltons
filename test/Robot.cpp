#include <gtest/gtest.h>

#include "Robot.h"

TEST(Robot_moveDirection, UP)
{
    Robot robot(RED, 0, 0);
    robot.move(UP);
    EXPECT_EQ(robot.getX(), 0);
    EXPECT_EQ(robot.getY(), -1);
}

TEST(Robot_moveDirection, DOWN)
{
    Robot robot(RED, 0, 0);
    robot.move(DOWN);
    EXPECT_EQ(robot.getX(), 0);
    EXPECT_EQ(robot.getY(), 1);
}

TEST(Robot_moveDirection, LEFT)
{
    Robot robot(RED, 0, 0);
    robot.move(LEFT);
    EXPECT_EQ(robot.getX(), -1);
    EXPECT_EQ(robot.getY(), 0);
}

TEST(Robot_moveDirection, RIGHT)
{
    Robot robot(RED, 0, 0);
    robot.move(RIGHT);
    EXPECT_EQ(robot.getX(), 1);
    EXPECT_EQ(robot.getY(), 0);
}
