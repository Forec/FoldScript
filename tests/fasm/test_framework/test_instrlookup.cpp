//
// Created by 王耀 on 2017/10/8.
//

#include <gtest/gtest.h>
#include "inslktable.h"
#include "macro.h"

TEST(InstrLookupTest, InstrLookupTest_MANAGE_INSTR_LOOKUP_Test) {
    InstrLookupTable table;
    EXPECT_TRUE(table.addInstrLookup("mov", 1, 2));   // 添加 mov 指令，操作码 1，操作数 2 个
    EXPECT_FALSE(table.addInstrLookup("mov", 0, 0));  // 添加已有指令
    EXPECT_EQ(INSTR_MOV, table.getInstrLookup("mov").getOpCode()); // 添加的 mov 指令操作码为 INSTR_MOV
    EXPECT_EQ(2, table.getInstrLookup("mov").getOpCount()); // 添加的 mov 指令操作数个数为 1
    table.setInstrOpType("mov", 0, 2);  // 设定第 1 个操作数为类型 2
    table.setInstrOpType("mov", 1, 1);  // 设定第 2 个操作数为类型 1
    EXPECT_EQ(2, table.getInstrOpType("mov", 0));
    EXPECT_EQ(1, table.getInstrOpType("mov", 1));
}

TEST(InstrLookupTest, InstrLookupTest_INIT_INSTR_LOOKUP_Test) {
    InstrLookupTable table;
    table.init();
    EXPECT_EQ(0, table.getInstrLookup(INSTR_NOP_STR).getOpCount());
    EXPECT_EQ(OP_FLAG_TYPE_NORMAL, table.getInstrOpType(INSTR_SHL_STR, 1));
    EXPECT_EQ(INSTR_ADD, table.getInstrLookup("Add").getOpCode()); // 添加的 add 指令操作吗为 INSTR_ADD
}