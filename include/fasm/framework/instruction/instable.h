//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_INSTABLE_H
#define FOLDSCRIPT_INSTABLE_H

/*
 * InstrTable: 代码查找表
 */

#include "instr.h"
#include <vector>

class InstrTable {
private:
    std::vector<Instr> instrStream;
public:
    InstrTable();
    ~InstrTable();
    void reset();
    void resize(unsigned long);
    unsigned long getSize();
    void addInstr(const Instr& ins);
    Instr getInstr(unsigned long index);
    void setInstr(unsigned long index, const Instr &instr);
    void setOpCode(unsigned long index, unsigned int opCode);
    void setOpCount(unsigned long index, unsigned int opCount);
    void setOpList(unsigned long index, const std::vector<Op> & opList);
};

#endif //FOLDSCRIPT_INSTABLE_H
