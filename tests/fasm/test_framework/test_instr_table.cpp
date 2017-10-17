//
// Created by 王耀 on 2017/10/18.
//

#include <gtest/gtest.h>
#include "instable.h"

TEST(InstructionTable, InstructionTable_MANAGE_Test) {
    InstrTable table;
    EXPECT_EQ(0, table.getSize());
    Instr instr1(1, 0);
    table.addInstr(instr1);
    EXPECT_EQ(1, table.getSize());
    table.addInstr(instr1);
    EXPECT_EQ(2, table.getSize());
    Instr instr2 = table.getInstr(1);
    EXPECT_EQ(1, instr2.uiOpCode);
    EXPECT_EQ(0, instr2.uiOpCount);
    Instr instr3(2, 1);
    table.setInstr(0, instr3);
    EXPECT_EQ(2, table.getSize());
    EXPECT_EQ(2, table.getInstr(0).uiOpCode);
    EXPECT_EQ(1, table.getInstr(0).uiOpCount);
}