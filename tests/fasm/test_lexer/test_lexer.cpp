//
// Created by 王耀 on 2017/10/10.
//

#include <gtest/gtest.h>
#include "macro.h"
#include "source.h"
#include "lexer.h"

TEST(LexerTest, LexerTest_RESET_Test) {
    SourceCode::initFromString("   var X;声明X \n");
    SourceCode::getInstance()->stripComments();
    SourceCode::getInstance()->trimWhitespace();

    Lexer lexer;
    EXPECT_EQ(TOKEN_TYPE_INVALID, lexer.getCurrentToken());
    EXPECT_EQ(LEX_STATE_NO_STRING, lexer.getCurrentState());
    EXPECT_TRUE(lexer.getCurrentLexeme().empty());
}