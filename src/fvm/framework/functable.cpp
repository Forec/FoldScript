//
// Created by 王耀 on 2017/11/12.
//

#include "functable.h"

Func::Func() {
    uiEntryPoint = 0;
    uiParamCount = 0;
    uiLocalDataSize = 0;
    uiStackFrameSize = 0;
}

Func::Func(unsigned int entryPoint,
           unsigned int paramCount,
           unsigned int localDataSize,
           unsigned int stackFrameSize) {
    uiEntryPoint = entryPoint;
    uiParamCount = paramCount;
    uiLocalDataSize = localDataSize;
    uiStackFrameSize = stackFrameSize;
}

FuncTable::FuncTable() {
    reset();
}

FuncTable::~FuncTable() {
    reset();
}

void FuncTable::reset() {
    functions.clear();
}

void FuncTable::append(Func function) {
    functions.emplace_back(function);
}

Func FuncTable::getFunction(unsigned long index) {
    if (index >= functions.size())
        return Func{};
    return functions.at(index);
}

unsigned long FuncTable::getSize() {
    return functions.size();
}