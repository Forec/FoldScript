//
// Created by 王耀 on 2017/10/10.
//

#include <gtest/gtest.h>
#include "source.h"

TEST(TestSource, TestSource_STRING_MODIFIERS_Test) {
    /*
     * Test Code:
     * (4space)mov X, 1(\t);给 X 赋值为1(space)
     * (empty line)
     * (4space)shl X, 2;将 X 左移 2 位(\t)(space)
     * (2space)var(\t)Y(2space)
     * (2space)mov(\t)Y, X(4space);将 Y 赋值给 X
     *
     */
    SourceCode source;
    source.initFromString("    mov X, 1\t;给 X 赋值为 1 \n\n    shl X, 2;将 X 左移 2 位\t \n  var\tY  \n  mov\tY, X    ;将 Y 赋值给 X\n");
    EXPECT_TRUE(source.isInitialized());
    EXPECT_EQ(6, source.getSize());
    source.stripComments();
    EXPECT_EQ("    mov X, 1\t", source.readLine(0));
    EXPECT_TRUE(source.readLine(1).empty());
    EXPECT_EQ("    shl X, 2", source.readLine(2));
    EXPECT_EQ("  var\tY  ", source.readLine(3));
    EXPECT_EQ("  mov\tY, X    ", source.readLine(4));
    EXPECT_TRUE(source.readLine(5).empty());

    source.trimWhitespace();
    EXPECT_EQ(4, source.getSize());   // 去除 2 行空行
    EXPECT_EQ("mov X, 1", source.readLine(0));
    EXPECT_EQ("shl X, 2", source.readLine(1));
    EXPECT_EQ("var\tY", source.readLine(2));
    EXPECT_EQ("mov\tY, X", source.readLine(3));
}