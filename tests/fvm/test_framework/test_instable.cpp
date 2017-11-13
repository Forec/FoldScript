//
// Created by 王耀 on 2017/11/13.
//

#include <vector>
#include <gtest/gtest.h>
#include "value.h"
#include "instable.h"
#include "macro.h"

TEST(InstrTableTest, InstrTableTest_INIT_Test) {
    InstrTable instable;
    EXPECT_EQ(0, instable.getSize());
}

TEST(InstrTableTest, InstrTableTest_RESIZE_Test) {
    InstrTable instable;
    EXPECT_EQ(0, instable.getSize());
    instable.setSize(5);
    EXPECT_EQ(5, instable.getSize());
}

TEST(InstrTableTest, InstrTableTest_OP_Test) {
    InstrTable instable;
    instable.setSize(4);
    instable.setOpCode(3, INSTR_XOR);
    instable.setOpCount(2, 2);
    std::vector<Value> valueList;
    Value v1, v2;
    v1.iType = OP_TYPE_INT; v1.iIntLiteral = 32;
    v2.iType = OP_TYPE_STRING; v2.sStrLiteral = "testFVM";
    valueList.emplace_back(v1);
    valueList.emplace_back(v2);
    instable.setValueList(1, valueList);

    EXPECT_EQ(4, instable.getSize());
    EXPECT_EQ(INSTR_XOR, instable.getInstr(3).uiOpCode);
    EXPECT_EQ(2, instable.getInstr(2).uiOpCount);
    EXPECT_EQ(2, instable.getInstr(1).ValueList.size());
    EXPECT_EQ(OP_TYPE_INT, instable.getInstr(1).getOp(0).iType);
    EXPECT_EQ(OP_TYPE_STRING, instable.getInstr(1).getOp(1).iType);
    EXPECT_EQ(32, instable.getInstr(1).getOp(0).iIntLiteral);
    EXPECT_EQ("testFVM", instable.getInstr(1).getOp(1).sStrLiteral);
}
