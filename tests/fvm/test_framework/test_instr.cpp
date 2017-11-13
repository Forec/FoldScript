//
// Created by 王耀 on 2017/11/14.
//

#include <vector>
#include <gtest/gtest.h>
#include "value.h"
#include "instr.h"
#include "macro.h"

TEST(InstrTest, InstrTest_OPERATION_Test) {
    Instr instruction1;
    EXPECT_EQ(INSTR_NOP, instruction1.uiOpCode);
    EXPECT_EQ(0, instruction1.uiOpCount);

    std::vector<Value> valueList;
    Value value;
    value.iType = OP_TYPE_FLOAT;
    value.fFloatLiteral = 0.512;
    valueList.emplace_back(value);

    Instr instruction2(INSTR_INC, 1, valueList);
    EXPECT_EQ(INSTR_INC, instruction2.uiOpCode);
    EXPECT_EQ(1, instruction2.uiOpCount);
    EXPECT_EQ(value, instruction2.getOp(0));
}