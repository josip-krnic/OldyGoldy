#include <gtest/gtest.h>

// Simple function to test
int add(int a, int b)
{
    return a + b;
}

// Unit tests
TEST(MathTests, AddsPositiveNumbers)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(MathTests, AddsNegativeNumbers)
{
    EXPECT_EQ(add(-2, -3), -5);
}

TEST(MathTests, AddsZero)
{
    EXPECT_EQ(add(5, 0), 5);
}
