//
// Created by 王耀 on 2017/10/8.
//

#include <gtest/gtest.h>
#include "labtable.h"

TEST(LabelTest, LabelTest_MANAGE_LABEL_Test) {
    LabelTable lt;
    EXPECT_EQ(0, lt.addLabel("label0", 12, 1));  // 添加函数索引 1 中的指令 12 处的标签 label0
    EXPECT_EQ(1, lt.addLabel("label0", 4, 2));   // 添加函数索引 2 中的指令 4 处的标签 label0
    EXPECT_EQ(2, lt.addLabel("label1", 2, 1));   // 添加函数索引 1 中的指令 2 处的标签 label1
    EXPECT_EQ(-1, lt.addLabel("label0", 0, 1));  // 冲突标签
    EXPECT_EQ(-1, lt.getLabel("label", 0).getIndex());  // 获取不存在的 label
    EXPECT_EQ(2, lt.getLabel("label1", 1).getIndex());
}