//
// Created by 王耀 on 2017/11/12.
// 此文件部分同步自 fasm/framework/instruction/instable.h
//

#ifndef FOLDSCRIPT_VM_INSTABLE_H
#define FOLDSCRIPT_VM_INSTABLE_H

/*
 * InstrTable: 指令表
 * @uiSize: 指令表长度固定
 */


#include "instr.h"
#include <vector>

class InstrTable {
private:
    std::vector<Instr> instrStream;
    unsigned int uiSize;
    unsigned int uiCurrentInstrIndex;
public:
    InstrTable();
    ~InstrTable();
    void reset();
    void fit();
    void setSize(unsigned int size);
    unsigned long getSize();
    unsigned int getCurrentIndex();
    void addInstr(const Instr& ins);
    Instr getInstr(unsigned long index);
    Instr getCurrentInstr();
    int getOpType(unsigned int uiOpIndex);
    void setInstr(unsigned long index, const Instr &instr);
    void setOpCode(unsigned long index, unsigned int opCode);
    void setOpCount(unsigned long index, unsigned int opCount);
    void setValueList(unsigned long index, const std::vector<Value> & valueList);
};

#endif //FOLDSCRIPT_VM_INSTABLE_H
