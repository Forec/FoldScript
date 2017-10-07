//
// Created by 王耀 on 2017/10/7.
//

#include <gtest/gtest.h>
#include "utils.h"

TEST(UtilsTest, UtilsTest_IS_CHAR_NUMERIC_Test) {
    EXPECT_TRUE(isCharNumeric('0'));
    EXPECT_TRUE(isCharNumeric('9'));
    EXPECT_FALSE(isCharNumeric('a'));
    EXPECT_FALSE(isCharNumeric('O'));
}

TEST(UtilsTest, UtilsTest_IS_CHAR_WHITESPACE_Test) {
    EXPECT_TRUE(isCharWhitespace('\t'));
    EXPECT_TRUE(isCharWhitespace(' '));
    EXPECT_TRUE(isCharWhitespace('\n'));
    EXPECT_FALSE(isCharWhitespace('t'));
    EXPECT_FALSE(isCharWhitespace('0'));
}

TEST(UtilsTest, UtilsTest_IS_CHAR_IDENT_Test) {
    EXPECT_TRUE(isCharIdent('_'));
    EXPECT_TRUE(isCharIdent('9'));
    EXPECT_TRUE(isCharIdent('a'));
    EXPECT_TRUE(isCharIdent('A'));
    EXPECT_FALSE(isCharIdent('('));
    EXPECT_FALSE(isCharIdent('\n'));
    EXPECT_FALSE(isCharIdent(' '));
}

TEST(UtilsText, UtilsTest_IS_CHAR_DELIMITER_Test) {
    EXPECT_TRUE(isCharDelimiter(':'));
    EXPECT_TRUE(isCharDelimiter(','));
    EXPECT_TRUE(isCharDelimiter('"'));
    EXPECT_TRUE(isCharDelimiter('['));
    EXPECT_TRUE(isCharDelimiter(']'));
    EXPECT_TRUE(isCharDelimiter('{'));
    EXPECT_TRUE(isCharDelimiter('}'));
    EXPECT_FALSE(isCharDelimiter('a'));
    EXPECT_FALSE(isCharDelimiter('0'));
}

TEST(UtilsTest, UtilsTest_IS_STRING_INT_Test) {
    EXPECT_TRUE(isStringInt("0"));
    EXPECT_TRUE(isStringInt("032811"));
    EXPECT_TRUE(isStringInt("-032811"));
    EXPECT_FALSE(isStringInt(""));
    EXPECT_FALSE(isStringInt("321-32-4"));
    EXPECT_FALSE(isStringInt("3213.321"));
    EXPECT_FALSE(isStringInt("099a89"));
}

TEST(UtilsTest, UtilsTest_IS_STRING_FLOAT_Test) {
    EXPECT_TRUE(isStringFloat("0.0"));
    EXPECT_FALSE(isStringFloat(""));;
    EXPECT_FALSE(isStringFloat("0"));
    EXPECT_TRUE(isStringFloat(".1423"));
    EXPECT_TRUE(isStringFloat("-0.312"));
    EXPECT_TRUE(isStringFloat("-.31242"));
    EXPECT_TRUE(isStringFloat("142483."));
    EXPECT_TRUE(isStringFloat("."));
    EXPECT_FALSE(isStringFloat("--12312"));
    EXPECT_FALSE(isStringFloat("--12312.123"));
    EXPECT_FALSE(isStringFloat("412930.132.321"));
    EXPECT_FALSE(isStringFloat(".."));
    EXPECT_FALSE(isStringFloat("90.312132-312"));
}

TEST(UtilsTest, UtilsTest_IS_STRING_SPACE_Test) {
    EXPECT_TRUE(isStringSpace("  \t   \n  "));
    EXPECT_FALSE(isStringSpace("  \t   a  "));
    EXPECT_FALSE(isStringSpace(""));
}

TEST(UtilsTest, UtilsTest_IS_STRING_IDENT_Test) {
    EXPECT_TRUE(isStringIdent("_IsStringIdent"));
    EXPECT_TRUE(isStringIdent("abcde"));
    EXPECT_TRUE(isStringIdent("a9f_fd"));
    EXPECT_TRUE(isStringIdent("___"));
    EXPECT_FALSE(isStringIdent(""));
    EXPECT_FALSE(isStringIdent("\nklas"));
    EXPECT_FALSE(isStringIdent(" fdasio"));
    EXPECT_FALSE(isStringIdent("9afA"));
    EXPECT_FALSE(isStringIdent("0AA"));
}