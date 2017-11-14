//
// Created by 王耀 on 2017/11/14.
//

#include <gtest/gtest.h>
#include "value.h"
#include "macro.h"

TEST(ValueTest, ValueTest_COERCE_Test) {
    Value v1, v2, v3;
    v1.iType = OP_TYPE_INT;
    v2.iType = OP_TYPE_INSTR_INDEX;
    v3.iType = OP_TYPE_HOST_API_CALL_INDEX;
    v1.iIntLiteral = -3;
    v2.iFuncIndex = 30;
    v3.uiHostAPICallIndex = 2;
    EXPECT_EQ(-3, v1.toInt());
    EXPECT_EQ(30, v2.toInstrIndex());
    EXPECT_EQ(2, v3.toHostApiIndex());
    EXPECT_EQ(0xFF, v1.toHostApiIndex());
    EXPECT_EQ("-3", v1.toString());
    EXPECT_TRUE(v2.toString().empty());
    EXPECT_TRUE(v3.toString().empty());
}

TEST(ValueTest, ValueTest_EQUAL_Test) {
    Value v1, v2;
    v1.iType = OP_TYPE_INT;
    v2.iType = OP_TYPE_INT;
    v1.iIntLiteral = 3; v2.iIntLiteral = 4;
    EXPECT_FALSE(v1 == v2);
    v2.iIntLiteral = 3;
    EXPECT_TRUE(v1 == v2);
    v1.iType = OP_TYPE_NULL;
    EXPECT_FALSE(v1 == v2);
    v2.iType = OP_TYPE_NULL;
    EXPECT_TRUE(v1 == v2);
    v1.iType = OP_TYPE_REL_STACK_INDEX;
    v2.iType = OP_TYPE_REL_STACK_INDEX;
    v1.iStackIndex = 3; v2.iStackIndex = 3;
    v1.iOffsetIndex = 4; v2.iOffsetIndex = -1;
    EXPECT_FALSE(v1 == v2);
    v1.iOffsetIndex = -1;
    EXPECT_TRUE(v1 == v2);
}