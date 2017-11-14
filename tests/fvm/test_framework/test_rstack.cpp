//
// Created by 王耀 on 2017/11/14.
//

#include <gtest/gtest.h>
#include "macro.h"
#include "value.h"
#include "rstack.h"

TEST(RStackTest, RStackTest_INIT_Test) {
    RuntimeStack stack;
    EXPECT_EQ(0, stack.getSize());
}

TEST(RStackTest, RStackTest_PUSH_Test) {
    RuntimeStack stack;
    Value value;
    value.iType = OP_TYPE_INT;
    value.iIntLiteral = 32;
    EXPECT_FALSE(stack.push(value));
    stack.setSize(1);
    stack.fit();
    EXPECT_EQ(1, stack.getSize());
    EXPECT_TRUE(stack.push(value));
}

TEST(RStackTest, RStackTest_POP_Test) {
    RuntimeStack stack;
    Value value;
    value.iType = OP_TYPE_INT;
    value.iIntLiteral = 30;
    stack.setSize(1);
    stack.fit();
    EXPECT_TRUE(stack.push(value));
    Value v2 = stack.pop();
    EXPECT_EQ(OP_TYPE_INT, v2.iType);
    EXPECT_EQ(30, v2.iIntLiteral);
}

TEST(RStackTest, RStackTest_SET_Test) {
    RuntimeStack stack;
    EXPECT_EQ(0, stack.getSize());
    Value value;
    value.iType = OP_TYPE_STRING;
    value.sStrLiteral = "testSet";
    EXPECT_FALSE(stack.setValue(0, value));
    stack.setSize(10);
    stack.fit();
    EXPECT_TRUE(stack.setValue(2, value));
    Value v2 = stack.getValue(2);
    EXPECT_EQ(OP_TYPE_STRING, v2.iType);
    EXPECT_EQ("testSet", v2.sStrLiteral);
}

TEST(RStackTest, RStackTest_INDEX_Test) {
    RuntimeStack stack;
    EXPECT_EQ(0, stack.getSize());
    stack.setSize(40);
    stack.fit();
    EXPECT_EQ(40, stack.getSize());
    stack.pushFrame(20);
    EXPECT_EQ(17, stack.resolveIndex(-3));
    EXPECT_EQ(23, stack.resolveIndex(23));
}

TEST(RStackTest, RStackTest_VALUE_REF_Test) {
    RuntimeStack stack;
    EXPECT_EQ(0, stack.getSize());
    Value value;
    value.iType = OP_TYPE_REG;
    value.uiReg = 3;
    stack.setSize(3);
    stack.fit();
    stack.push(value);
    Value & v = stack.getValueRef(0);
    v.uiReg = 10;
    EXPECT_EQ(OP_TYPE_REG, v.iType);
    Value v2 = stack.getValue(0);
    EXPECT_EQ(10, v2.uiReg);
}