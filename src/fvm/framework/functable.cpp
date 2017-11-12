//
// Created by 王耀 on 2017/11/12.
//

#include "functable.h"

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
        return Func{0, 0, 0, 0};
    return functions.at(index);
}