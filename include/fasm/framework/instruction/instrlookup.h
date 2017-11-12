//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_ASM_INSTRLOOKUP_H
#define FOLDSCRIPT_ASM_INSTRLOOKUP_H

#include <vector>

/*
 * InstrLoopup: 指令查找项
 * @uiOpCode: 指令操作码
 * @uiOpCount: 指令操作数数量
 * @OpList: 指令操作数列表
 */

typedef unsigned char OpTypes;

class InstrLookup {
private:
    unsigned int uiOpCode;
    unsigned int uiOpCount;
    std::vector<OpTypes> OpList;
public:
    InstrLookup(unsigned int opCode, unsigned int opCount);
    void setOpType(unsigned int opIndex, OpTypes type);
    OpTypes getOpType(unsigned int opIndex);
    unsigned int getOpCode() { return uiOpCode; }
    unsigned int getOpCount() { return uiOpCount; }
};

#endif //FOLDSCRIPT_ASM_INSTRLOOKUP_H
