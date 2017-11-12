//
// Created by 王耀 on 2017/11/12.
// 此文件同步自 fasm/framework/instruction/instable.h
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
public:
    InstrTable();
    ~InstrTable();
    void reset();
    void fit();
    void setSize(unsigned int size);
    unsigned long getSize();
    void addInstr(const Instr& ins);
    Instr getInstr(unsigned long index);
    void setInstr(unsigned long index, const Instr &instr);
    void setOpCode(unsigned long index, unsigned int opCode);
    void setOpCount(unsigned long index, unsigned int opCount);
    void setValueList(unsigned long index, const std::vector<Value> & valueList);
};

#endif //FOLDSCRIPT_VM_INSTABLE_H
