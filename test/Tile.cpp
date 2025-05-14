#include <gtest/gtest.h>

#include "Tile.h"

TEST(Tile_getEmoji, RED_TRIANGLE)
{
    EXPECT_STREQ(Tile(RED, TRIANGLE).getEmoji().c_str(), "\033[31m▲ \033[0m");
}

TEST(Tile_getEmoji, RED_CIRCLE)
{
    EXPECT_STREQ(Tile(RED, CIRCLE).getEmoji().c_str(), "\033[31m● \033[0m");
}

TEST(Tile_getEmoji, RED_SQUARE)
{
    EXPECT_STREQ(Tile(RED, SQUARE).getEmoji().c_str(), "\033[31m■ \033[0m");
}

TEST(Tile_getEmoji, RED_STAR)
{
#ifdef _WIN32
    EXPECT_STREQ(Tile(RED, STAR).getEmoji().c_str(), "\033[31m※ \033[0m");
#else
    EXPECT_STREQ(Tile(RED, STAR).getEmoji().c_str(), "\033[31m🟊 \033[0m");
#endif
}

TEST(Tile_getEmoji, RAINBOW)
{
    EXPECT_STREQ(Tile(RAINBOW, STAR).getEmoji().c_str(), u8"🌈");
}