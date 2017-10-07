//
// Created by 王耀 on 2017/10/7.
//

#include "instr.h"

Instr::Instr(unsigned int opCode, unsigned int opCount) {
    iOpCode = opCode;
    iOpCount = opCount;
    iOpList.clear();
}

Instr::Instr(unsigned int opCode, unsigned int opCount, const std::vector<Op> &opList) {
    new (this)Instr(opCode, opCount);
    iOpList = opList;
}