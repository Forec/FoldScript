//
// Created by 王耀 on 2017/11/12.
// 此文件部分同步自 fasm/framework/instruction/instr.h
//

#ifndef FOLDSCRIPT_VM_INSTR_H
#define FOLDSCRIPT_VM_INSTR_H

#include "../value.h"
#include <vector>

/*
 * Instr: 指令
 * @uiOpCode: 操作码
 * @uiOpCount: 操作数个数
 * @ValueList: 操作数列表
 */

struct Instr {
    unsigned int uiOpCode;
    unsigned int uiOpCount;
    std::vector<Value> ValueList;
    explicit Instr(unsigned int opCode, unsigned int opCount = 0);
    Instr(unsigned int opCode, unsigned int opCount, const std::vector<Value> &valueList);
    Value getOp(unsigned int index);
};

#endif //FOLDSCRIPT_VM_INSTR_H
