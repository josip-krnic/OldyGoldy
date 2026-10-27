#include <gtest/gtest.h>

// Simple function to test
int mul(int a, int b)
{
    return a * b;
}

// Unit tests
TEST(MathTests, MultiplyPositiveNumbers)
{
    EXPECT_EQ(mul(2, 3), 6);
}

TEST(MathTests, MultiplyNegativeNumbers)
{
    EXPECT_EQ(mul(-2, -3), 6);
}

TEST(MathTests, MultiplyZero)
{
    EXPECT_EQ(mul(5, 0), 0);
}
