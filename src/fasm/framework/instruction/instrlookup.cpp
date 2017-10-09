//
// Created by 王耀 on 2017/10/8.
//

#include "instrlookup.h"

InstrLookup::InstrLookup(unsigned int opCode, unsigned int opCount) {
    uiOpCode = opCode;
    uiOpCount = opCount;
    OpList.resize(opCount, 0);
}

void InstrLookup::setOpType(unsigned int opIndex, OpTypes type) {
    if (opIndex >= uiOpCount)
        return;
    if (OpList.size() < uiOpCount)
        OpList.resize(uiOpCount, 0);
    OpList[opIndex] = type;
}

OpTypes InstrLookup::getOpType(unsigned int opIndex) {
    if (opIndex >= uiOpCount)
        return 0;
    if (OpList.size() < uiOpCount)
        OpList.resize(uiOpCount, 0);
    return OpList[opIndex];
}