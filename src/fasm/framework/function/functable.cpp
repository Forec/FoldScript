//
// Created by 王耀 on 2017/10/7.
//

#include "functable.h"

FuncTable::FuncTable() {
    iTable.clear();
}

FuncTable::~FuncTable() {
    iTable.clear();
}

void FuncTable::reset() {
    iTable.clear();
}

int FuncTable::addFunction(const std::string &name, int entryPoint) {
    if (iTable.find(name) != iTable.end())                              // 已存在同名函数，返回无效索引
        return -1;
    FuncNode func((int)iTable.size(), entryPoint);
    iTable.insert(std::make_pair(name, func));
    return func.getIndex();
}

void FuncTable::setFunction(const std::string &name, unsigned int paramCount, unsigned int localDataSize) {
    auto pair = iTable.find(name);
    if (pair == iTable.end())
        return;
    pair->second.setParamCount(paramCount);
    pair->second.setLocalDataSize(localDataSize);
}

FuncNode FuncTable::getFunction(const std::string &name) {
    auto pair = iTable.find(name);
    if (pair == iTable.end())
        return FuncNode{-1, -1, 0, 0};
    return pair->second;
}