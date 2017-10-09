//
// Created by 王耀 on 2017/10/7.
//

#ifndef FOLDSCRIPT_INSTR_H
#define FOLDSCRIPT_INSTR_H

#include "../op.h"
#include <vector>

/*
 * Instr: 指令
 * @iOpCode: 操作码
 * @iOpCount: 操作数个数
 * @iOpList: 操作数列表
 */

struct Instr {
    unsigned int uiOpCode;
    unsigned int uiOpCount;
    std::vector<Op> OpList;
    explicit Instr(unsigned int opCode, unsigned int opCount = 0);
    Instr(unsigned int opCode, unsigned int opCount, const std::vector<Op> &opList);
};

#endif //FOLDSCRIPT_INSTR_H
