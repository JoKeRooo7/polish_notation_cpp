#include <gtest/gtest.h>
#include "../src/polish_notation_plus.h"

#include <iostream>


TEST(TestPolishNotation, Test1) {
    jokerooo7::PolishNotation obj("");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"");
}

TEST(TestPolishNotation, Test2) {
    jokerooo7::PolishNotation obj("1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1 ");
}

TEST(TestPolishNotation, Test3) {
    jokerooo7::PolishNotation obj("-1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- ");
}

TEST(TestPolishNotation, Test4) {
    jokerooo7::PolishNotation obj("-1 + 1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1 + ");
}

TEST(TestPolishNotation, Test5) {
    jokerooo7::PolishNotation obj("-1 +- 1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- + ");
}

TEST(TestPolishNotation, Test6) {
    jokerooo7::PolishNotation obj("-1 +- (1)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- 1 * + ");
}

TEST(TestPolishNotation, Test7) {
    jokerooo7::PolishNotation obj("-1 +- (-1)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- 1- * + ");
}

TEST(TestPolishNotation, Test8) {
    jokerooo7::PolishNotation obj("-sin(-1)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- sin * ");
}

TEST(TestPolishNotation, Test9) {
    jokerooo7::PolishNotation obj("- arcsin(-1)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- arcsin * ");
}

TEST(TestPolishNotation, Test10) {
    jokerooo7::PolishNotation obj("sin(cos(tan(-0.12)))");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"0.12- tan cos sin ");
}

TEST(TestPolishNotation, Test11) {
    jokerooo7::PolishNotation obj("-(-(-(-(-(-5)))))");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1- 1- 1- 1- 5- * * * * * ");
}

TEST(TestPolishNotation, Test12) {
    jokerooo7::PolishNotation obj("2 ^ 3 ^ 4 ^ 5");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"2 3 4 5 ^ ^ ^ ");
}

TEST(TestPolishNotation, Test13) {
    jokerooo7::PolishNotation obj; 
    obj = ("(ln(0.01) - sqrt(0.912) *- cos(123)) mod(9.55)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"0.01 ln 0.912 sqrt 1- 123 cos * * - 9.55 mod ");
}

TEST(TestPolishNotation, Test14) {
    jokerooo7::PolishNotation obj("log(arctan(0.2) + 2 ^ -3 ^ sin(123.0))");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"0.2 arctan 2 3- 123.0 sin ^ ^ + log ");
}

TEST(TestPolishNotation, Test15) {
    jokerooo7::PolishNotation obj("5 / 6 / 7 /- 8 ");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"5 6 / 7 / 8- / ");
}

TEST(TestPolishNotation, Test16) {
    EXPECT_THROW(jokerooo7::PolishNotation obj("µ"), std::invalid_argument);
}

TEST(TestPolishNotation, Test17) {
    jokerooo7::PolishNotation obj("-1 -1 --1 +1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1 - 1- - 1 + ");
}

TEST(TestPolishNotation, Test18) {
    jokerooo7::PolishNotation obj("-1 -1 --1 +1");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"1- 1 - 1- - 1 + ");
}

TEST(TestPolishNotation, Test19) {
    jokerooo7::PolishNotation obj(L"√(24)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"24 √ ");
}

TEST(TestPolishNotation, Test20) {
    jokerooo7::PolishNotation obj(L"cos(π) + sin(π)");
    EXPECT_EQ(obj.w_get_postfix_entry(), L"\x3C0 cos \x3C0 sin + ");
}