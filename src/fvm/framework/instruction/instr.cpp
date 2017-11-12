//
// Created by 王耀 on 2017/11/12.
// 此文件同步自 fasm/framework/instruction/instr.cpp
//

#include "instr.h"

Instr::Instr(unsigned int opCode, unsigned int opCount) {
    uiOpCode = opCode;
    uiOpCount = opCount;
    ValueList.clear();
}

Instr::Instr(unsigned int opCode, unsigned int opCount, const std::vector<Value> &valueList) {
    new (this)Instr(opCode, opCount);
    ValueList = valueList;
}