//
// Created by 王耀 on 2017/10/8.
//

#include <gtest/gtest.h>
#include "symtable.h"

TEST(SymbolTest, SymbolTest_MANAGE_SYMBOL_Test) {
    SymbolTable st;
    EXPECT_EQ(0, st.addSymbol("X", 1, 0, 0));   // 全局变量 X
    EXPECT_EQ(1, st.addSymbol("LX", 2, -4, 1)); // 函数索引为 1 下的局部变量 LX
    EXPECT_EQ(-1, st.addSymbol("X", 20, 4, 2)); // 与全局变量 X 冲突

    SymbolNode node;
    node = st.getSymbol("X", 1);     // 尝试获取函数索引为 1 下的变量 X，得到全局变量 X
    EXPECT_EQ(0, node.getIndex());
    EXPECT_EQ(0, node.getStackIndex());
    EXPECT_EQ(1, node.getSize());

    node = st.getSymbol("LX", 1);    // 获取函数索引为 1 下的变量 LX
    EXPECT_EQ(1, node.getIndex());
    EXPECT_EQ(-4, node.getStackIndex());
    EXPECT_EQ(2, node.getSize());

    EXPECT_EQ(-1, st.getSymbol("Unknown").getIndex()); // 未声明符号的索引为 -1

    EXPECT_EQ(-4, st.getStackIndex("LX", 1));
    EXPECT_EQ(0, st.getStackIndex("X", 1));
}