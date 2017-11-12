//
// Created by 王耀 on 2017/11/12.
//

#ifndef FOLDSCRIPT_VM_FUNCTABLE_H
#define FOLDSCRIPT_VM_FUNCTABLE_H

#include <vector>

struct Func {
    unsigned long ulEntryPoint;
    unsigned int uiParamCount;
    unsigned long ulLocalDataSize;
    unsigned long ulStackFrameSize;
};

class FuncTable {
private:
    std::vector<Func> functions;
public:
    FuncTable();
    ~FuncTable();
    void reset();
    void append(Func function);
    Func getFunction(unsigned long index);
};

#endif //FOLDSCRIPT_VM_FUNCTABLE_H
