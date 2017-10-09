//
// Created by 王耀 on 2017/10/7.
//

#include "instruction/instr.h"

Instr::Instr(unsigned int opCode, unsigned int opCount) {
    uiOpCode = opCode;
    uiOpCount = opCount;
    OpList.clear();
}

Instr::Instr(unsigned int opCode, unsigned int opCount, const std::vector<Op> &opList) {
    new (this)Instr(opCode, opCount);
    OpList = opList;
}