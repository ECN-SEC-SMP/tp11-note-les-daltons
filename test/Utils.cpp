#include <gtest/gtest.h>

#include "Utils.h"

TEST(Utils, getRandomNumber)
{
    newRandomSeed();
    int number = getRandomNumber(5);
    EXPECT_TRUE(number >= 0) << "Above 0";
    EXPECT_TRUE(number <= 5) << "Under Max";
}

TEST(Utils, is_number)
{
    std::string str = "is_not_a_number";
    EXPECT_FALSE(is_number(str)) << "is_not_a_number";
    str = "mix_58_of_4number_and96_letter";
    EXPECT_FALSE(is_number(str)) << "mix_58_of_4number_and96_letter";
    str = "95";
    EXPECT_TRUE(is_number(str)) << "95";
}

TEST(Utils, trim)
{
    std::string str = "with_no_space";
    EXPECT_STREQ(trim(str).c_str(), "with_no_space");
    str = "      with_leading_space";
    EXPECT_STREQ(trim(str).c_str(), "with_leading_space");
    str = "with_trailing_space     ";
    EXPECT_STREQ(trim(str).c_str(), "with_trailing_space");
    str = "     with_leading_and_trailing_space     ";
    EXPECT_STREQ(trim(str).c_str(), "with_leading_and_trailing_space");
    str = "     with_leading    and     trailing _space and space into     ";
    EXPECT_STREQ(trim(str).c_str(), "with_leading    and     trailing _space and space into");
}

TEST(Utils, reduce)
{
    std::string str = "with_no_space";
    EXPECT_STREQ(reduce(str).c_str(), "with_no_space");
    str = "      with_leading_space";
    EXPECT_STREQ(reduce(str).c_str(), "with_leading_space");
    str = "with_trailing_space     ";
    EXPECT_STREQ(reduce(str).c_str(), "with_trailing_space");
    str = "     with_leading_and_trailing_space     ";
    EXPECT_STREQ(reduce(str).c_str(), "with_leading_and_trailing_space");
    str = "     with_leading    and     trailing _space and space into     ";
    EXPECT_STREQ(reduce(str).c_str(), "with_leading and trailing _space and space into");
}
