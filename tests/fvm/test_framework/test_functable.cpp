//
// Created by 王耀 on 2017/11/14.
//

#include <gtest/gtest.h>
#include "functable.h"

TEST(FuncTableTest, FuncTableTest_OPERATION_Test) {
    Func func1(2, 3, 5, 9);
    FuncTable table;
    EXPECT_EQ(0, table.getSize());
    table.append(func1);
    EXPECT_EQ(1, table.getSize());
    EXPECT_EQ(0, table.getFunction(1).uiEntryPoint);
    EXPECT_EQ(9, table.getFunction(0).uiStackFrameSize);
}