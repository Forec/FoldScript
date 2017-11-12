//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_ASM_INSTR_H
#define FOLDSCRIPT_ASM_INSTR_H

#include "../op.h"
#include <vector>

/*
 * Instr: 指令
 * @uiOpCode: 操作码
 * @uiOpCount: 操作数个数
 * @OpList: 操作数列表
 */

struct Instr {
    unsigned int uiOpCode;
    unsigned int uiOpCount;
    std::vector<Op> OpList;
    explicit Instr(unsigned int opCode, unsigned int opCount = 0);
    Instr(unsigned int opCode, unsigned int opCount, const std::vector<Op> &opList);
};

#endif //FOLDSCRIPT_ASM_INSTR_H
