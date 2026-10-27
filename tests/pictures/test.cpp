#include <gtest/gtest.h>

// Simple function to test
int sub(int a, int b)
{
    return a - b;
}

// Unit tests
TEST(MathTests, SubstractPositiveNumbers)
{
    EXPECT_EQ(sub(2, 3), -1);
}

TEST(MathTests, SubstractNegativeNumbers)
{
    EXPECT_EQ(sub(-2, -3), 1);
}

TEST(MathTests, SubstractZero)
{
    EXPECT_EQ(sub(5, 0), 5);
}
