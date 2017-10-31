//
// Created by 王耀 on 2017/10/10.
//

#include <gtest/gtest.h>
#include "macro.h"
#include "source.h"
#include "lexer.h"

TEST(LexerTest, LexerTest_RESET_Test) {
    Lexer lexer;
    lexer.initFromString("   var X;声明X \n");
    EXPECT_EQ(TOKEN_TYPE_INVALID, lexer.getCurrentToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_TRUE(lexer.getCurrentLexeme().empty());
}

TEST(LexerTest, LexerTest_SKIPLINE_Test) {

    Lexer lexer;
    lexer.initFromString("var X; 声明X \n var Y\t\nmov X, Y");
    EXPECT_EQ(3, lexer.getSource()->getSize());
    EXPECT_TRUE(lexer.skipLine());  // currentSourceLine = 1
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_TRUE(lexer.skipLine());  // currentSourceLine = 2
    EXPECT_FALSE(lexer.skipLine());  // currentSourceLine = 3 >= 3
}

TEST(LexerTest, LexerTest_GET_NEXT_TOKEN_Test) {
    Lexer lexer;
    lexer.initFromString("Mov StringVal, \"This is a string\"\nVar YW; declare Y\nShl X, YW");
    EXPECT_EQ(3, lexer.getSource()->getSize());
    EXPECT_EQ(TOKEN_TYPE_INSTR, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("MOV", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_IDENT, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("STRINGVAL", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_COMMA, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ(",", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_QUOTE, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_IN_STRING, lexer.getCurrentState());
    EXPECT_EQ("\"", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_STRING, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_IN_STRING, lexer.getCurrentState());
    EXPECT_EQ("This is a string", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_QUOTE, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_END_STRING, lexer.getCurrentState());
    EXPECT_EQ("\"", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_VAR, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("VAR", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_IDENT, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("YW", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_INSTR, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("SHL", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_IDENT, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("X", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_COMMA, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ(",", lexer.getCurrentLexeme());

    EXPECT_EQ(TOKEN_TYPE_IDENT, lexer.getNextToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_EQ("YW", lexer.getCurrentLexeme());

    EXPECT_EQ(END_OF_TOKEN_STREAM, lexer.getNextToken());
}