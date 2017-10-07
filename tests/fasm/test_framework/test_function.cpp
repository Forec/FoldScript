//
// Created by 王耀 on 2017/10/7.
//

#include <gtest/gtest.h>
#include "functable.h"

TEST(FunctionTest, FunctionTest_ADD_FUNCTION_Test) {
    FuncTable ft;
    EXPECT_EQ(0, ft.addFunction("test_func0", 0));
    EXPECT_EQ(1, ft.addFunction("test_func1", 0));
    EXPECT_EQ(2, ft.addFunction("test_func2", 0));
    // 同名函数，返回无效索引
    EXPECT_EQ(-1, ft.addFunction("test_func0", 0));
}

TEST(FunctionTest, FunctionTest_SET_AND_GET_FUNCTION_Test) {
    FuncTable ft;
    EXPECT_EQ(0, ft.addFunction("getName", 12));
    ft.setFunction("getName", 2, 16); // 2 个参数，局部变量为 16 字节
    FuncNode node = ft.getFunction("getName");
    EXPECT_EQ(2, node.getParamCount());
    EXPECT_EQ(16, node.getLocalDataSize());
    EXPECT_EQ(12, node.getEntryPoint());
    EXPECT_EQ(0, node.getIndex());
}