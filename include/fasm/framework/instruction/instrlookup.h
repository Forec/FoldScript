//
// Created by 王耀 on 2017/10/8.
//

#ifndef FOLDSCRIPT_INSTRLOOKUP_H
#define FOLDSCRIPT_INSTRLOOKUP_H

#include <vector>

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

#endif //FOLDSCRIPT_INSTRLOOKUP_H
