//
// Created by 王耀 on 2017/10/7.
//

#include "functable.h"

FuncTable::FuncTable() {
    reset();
}

FuncTable::~FuncTable() {
    reset();
}

void FuncTable::reset() {
    iTable.clear();
    iNameList.clear();
}

unsigned long FuncTable::getSize() {
    return iTable.size();
}

std::vector<std::string> FuncTable::getNameList() {
    return iNameList;
}

int FuncTable::addFunction(const std::string &name, int entryPoint) {
    if (iTable.find(name) != iTable.end())                              // 已存在同名函数，返回无效索引
        return -1;
    FuncNode func((int)iTable.size(), entryPoint);
    iNameList.emplace_back(name);
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